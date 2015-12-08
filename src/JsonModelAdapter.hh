<?hh //strict
namespace Vodel;

use Vodel\Interfaces\JsonModel;

class JsonModelAdapter extends \ReflectionClass implements Interfaces\JsonAdapter
{

  protected Vector<string> $errors = Vector{};

  public function getErrors():Vector<string>
  {
    return $this->errors;
  }

  public function validate(\stdClass $object):bool
  {
    $this->errors->clear();
    $reflection = new \ReflectionClass($object);
    foreach($this->getProperties(\ReflectionProperty::IS_PUBLIC) as $property) {
      if(!$reflection->hasProperty($property->getName())) {
        $this->errors[] = "Missing property";
      } else {
        $jsonProperty = $reflection->getProperty($property->getName());
        if(!$this->checkType($property->getTypeText(), $jsonProperty->getValue($object))) {
          $this->errors[] = "Wrong type";
        }
      }
    }
    return $this->errors->count() == 0;
  }

  public function checkType(string $type, mixed $value):bool
  {
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

  public function fill(\stdClass $jsonObject):void
  {

  }


}
