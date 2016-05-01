<?hh //strict
namespace Vodel\Adapters;

use Vodel\Interfaces\JsonModel;
use Vodel\Interfaces\Validator;
use Vodel\PropertyInspector;
use Vodel\Interfaces\InputParameter;
use Vodel\ValidationRepository;
use Vodel\Input\ConstructorParameter;
use Vodel\Input\SetterMethod;
use Vodel\Input\PublicProperty;
use Vodel\Reflection\HackProperty;
use Vodel\Interfaces\TransformsData;

class ModelAdapter extends AdapterAbstract implements
  TransformsData<mixed, JsonModel>
{
  protected Vector<InputParameter> $input = Vector{};

  protected Map<string, mixed> $constructorArgs = Map{};

  public function __construct(
    protected ValidationRepository $validations,
    protected \ReflectionClass $reflection,
    public ?JsonModel $model = null
  ) {}

  protected function loadProperties(JsonModel $model):void
  {
    foreach($this->reflection->getProperties(\ReflectionProperty::IS_PUBLIC) as $property) {
      $this->input->add(new PublicProperty(
        new HackProperty($property),
        $this->validations->getValidatorFor($property->getTypeText()),
        $model
      ));
    }
  }

  protected function loadMethods(JsonModel $model):void
  {
    foreach($this->reflection->getMethods(\ReflectionMethod::IS_PUBLIC) as $method) {
      if(strpos($method->getName(), 'set') === 0) {
        $parameter = $method->getParameters()[0];
        $this->input->add(new SetterMethod(
          $method,
          $model,
          $this->validations->getValidatorFor($parameter->getTypeText())
        ));
      }
    }
  }

  public function validate(mixed $jsonObject):bool
  {
    if($jsonObject instanceof \stdClass) {
      $jsonReflection = new \ReflectionClass($jsonObject);
      foreach($this->getInputToValidate() as $property) {
        try {
          $property->extractValue($jsonReflection, $jsonObject);
          if(!$property->validate()) {
            $this->addFailMessage($property->getName(), $property->getValidator());
          }
        } catch(\ReflectionException $ex) {
          if(!$property->isOptional()) {
            $this->failures->add(Pair{$property->getName(), "Required"});
          }
        }
      }
    }
    return $this->failures->count() == 0;
  }

  protected function loadConstructorProperties():void
  {
    $constructor = $this->reflection->getConstructor();
    if($constructor !== null) {
      foreach($constructor->getParameters() as $parameter) {
        $this->input->add(new ConstructorParameter(
          $parameter,
          $this->validations->getValidatorFor($parameter->getTypeText()),
          $this->constructorArgs
        ));
      }
    }
  }

  protected function loadPropertiesAndMethods(JsonModel $model):void
  {
    $this->loadProperties($model);
    $this->loadMethods($model);
  }

  public function getInputToValidate():Vector<InputParameter>
  {
    if($this->model == null) {
      $this->loadConstructorProperties();
    } elseif($this->model !== null) {
      $this->loadPropertiesAndMethods($this->model);
    }
    return $this->input;
  }

  public function transform(mixed $value):JsonModel
  {
    foreach($this->input as $adapter) {
      if($adapter->getValue()){
        $adapter->applyValue();
      }
    }
    if($this->model == null) {
      return $this->reflection->newInstanceArgs($this->constructorArgs);
    }
    return $this->model;
  }

  public function getErrorMessage():string
  {
    return "Invalid input";
  }

}
