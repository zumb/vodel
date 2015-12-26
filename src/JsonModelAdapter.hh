<?hh //strict
namespace Vodel;

use Vodel\Interfaces\JsonModel;
use Vodel\Interfaces\Validator;

class JsonModelAdapter extends \ReflectionClass implements Interfaces\JsonAdapter
{
  protected Vector<string> $errors = Vector{};

  protected Map<string, Validator> $validators = Map{};

  public function addValidator(string $target, Validator $typeValidator):this
  {
    $this->validators->add(Pair{$target, $typeValidator});
    return $this;
  }

  public function getErrors():Vector<string>
  {
    return $this->errors;
  }

  public function validate(\stdClass $object):bool
  {
    $this->errors->clear();
    $reflection = new \ReflectionClass($object);
    foreach($this->getProperties(\ReflectionProperty::IS_PUBLIC) as $property) {
      $this->validateProperty($property, $reflection);
    }
    return $this->errors->count() == 0;
  }

  public function validateProperty(\ReflectionProperty $property, \ReflectionClass $jsonObject):void
  {
    if(!$jsonObject->hasProperty($property->getName()) && $property->isDefault()) {
      $this->errors[] = "Missing property";
    } else {
      $jsonProperty = $jsonObject->getProperty($property->getName());
      /*if(!$this->checkType($property->getTypeText(), $jsonProperty->getValue($object))) {
        $this->errors[] = "Wrong type";
      }*/
    }
  }

  public function checkType(string $type, mixed $value):bool
  {
    var_dump(is_a($value, $type));
    switch($type) {
      case 'HH\string':
        return is_string($value);
      default:
        $adapter = new JsonModelAdapter($type);
        if($value instanceof \stdClass && $adapter->implementsInterface(JsonModel::class)) {
          $this->errors->addAll($adapter->getErrors());
          return $adapter->validate($value);
        }
    }
    return false;
  }

  public function fillWith(\stdClass $jsonObject):void
  {

  }


}
