<?hh //strict
namespace Vodel;

use Vodel\Interfaces\JsonModel;
use Vodel\Interfaces\Validator;
use Vodel\ValidationCollection;

class JsonModelAdapter implements Validator
{
  public function __construct(
    protected PropertyAdapterFactory $factory,
    public \ReflectionClass $model
  ) {}

  public function validate(mixed $jsonObject):bool
  {
    if($jsonObject instanceof \stdClass) {
      $jsonObject = new \ReflectionClass($jsonObject);
      foreach($this->model->getProperties(\ReflectionProperty::IS_PUBLIC) as $property) {
        $adapter = $this->factory->make($property);
        if(!$adapter->validate($jsonObject->getProperty($property->getName()))) {
            return false;
        }
      }
      return true;
    }
    return false;
  }

}
