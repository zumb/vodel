<?hh //strict
namespace Vodel\Reflection;

use Vodel\Interfaces\JsonModel;

class TypeInspector
{
  public function isModel(string $type):bool
  {
    $implements = @class_implements($type);
    if($implements) {
      return in_array(JsonModel::class, $implements);
    }
    return false;
  }

  public function isVector(string $type):bool
  {
    return strpos($type, 'HH\Vector') !== false;
  }

  public function isEnum(string $type):bool
  {
    try {
      new \ReflectionMethod($type, "assert");
      return true;
    } catch (\ReflectionException $ex) {}
    return false;
  }

  public function getSubType(string $type):string
  {
    $matches = [];
    preg_match('/[^<]<(.*)>/', $type, $matches);
    return $matches[1];
  }

  public function getBasicType(string $type):string
  {
    $matches = [];
    preg_match('/\??([^<]*)/', $type, $matches);
    return $matches[1];
  }

}
