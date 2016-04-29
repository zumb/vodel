<?hh //strict
namespace Vodel;

use Vodel\Interfaces\JsonModel;
use Vodel\Interfaces\Validator;
use Vodel\ValidationCollection;
use Vodel\Validators\ComplexValidatorAbstract;
use Vodel\PropertyInspector;

class JsonModelAdapter
{
  public function __construct(
    protected ValidationRepository $validationRepository,
    public \ReflectionClass $model
  ) {}

  public function getProperties():array<PropertyAdapter>
  {
    $properties = [];
    foreach($this->model->getProperties(\ReflectionProperty::IS_PUBLIC) as $property) {
      $properties[] = $this->getAdapter($property);
    }
    return $properties;
  }

  public function getPropertiesFromMethods():array<PropertyAdapter>
  {
    $properties = [];
    foreach($this->model->getMethods(\ReflectionMethod::IS_PUBLIC) as $method) {
      if(strpos($method->getName(), 'set') === 0) {
        $parameter = $method->getParameters()[0];
        $properties[] = new PropertyAdapter(
          str_replace('set', '', $method->getName()),
          $parameter->getTypeText(),
          $this->validationRepository->getValidatorFor($parameter->getTypeText())
        );
      }
    }
    return $properties;
  }

  public function getPropertiesToValidate():array<PropertyAdapter>
  {
    return array_merge($this->getProperties(), $this->getPropertiesFromMethods());
  }

  public function getAdapter(\ReflectionProperty $property):PropertyAdapter
  {
    return new PropertyAdapter(
      $property->getName(),
      $property->getTypeText(),
      $this->validationRepository->getValidatorFor($property->getTypeText())
    );
  }

}
