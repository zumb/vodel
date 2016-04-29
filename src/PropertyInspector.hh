<?hh //strict
namespace Vodel;

use Vodel\Interfaces\JsonModel;

class PropertyInspector
{

  public function isModel(string $typeText):bool
  {
    $implements = @class_implements($typeText);
    if($implements) {
      return in_array(JsonModel::class, $implements);
    }
    return false;
  }

  public function isVector(string $typeText):bool
  {
    return strpos($typeText, 'HH\Vector') === 0;
  }

  public function getVectorType(string $typeText):string
  {
    $matches = [];
    preg_match('/HH\\\Vector<(.*)>/', $typeText, $matches);
    return $matches[1];
  }

  public function getReflectionClass(string $typeText):\ReflectionClass
  {
    return new \ReflectionClass($typeText);
  }

  public function getBasicType(string $typeText):string
  {
    $matches = [];
    preg_match('/\??([^<]*)/', $typeText, $matches);
    return $matches[1];
  }

  public function isEnum(string $typeText):bool
  {
    try {
      new \ReflectionMethod($typeText, "assert");
      return true;
    } catch (\ReflectionException $ex) {}
    return false;
  }

  public function isSubclass(string $child, string $parent):bool
  {
    $class = new \ReflectionClass($child);
    return $class->isSubclassOf($parent);
  }

  public function classExists(string $class):bool
  {
    return class_exists($class);
  }
}
