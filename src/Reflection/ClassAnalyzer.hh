<?hh //strict
namespace Zumb\Vodel\Reflection;

use Zumb\Vodel\Interfaces\JsonModel;
use Zumb\Vodel\ValidationRepository;
use Zumb\Vodel\Input\PublicProperty;
use Zumb\Vodel\Input\SetterMethod;
use Zumb\Vodel\Interfaces\InputParameter;
use Zumb\Vodel\Input\ConstructorParameter;
use Zumb\Vodel\Interfaces\TransformsData;

class ClassAnalyzer implements TransformsData<mixed, JsonModel>
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

}
