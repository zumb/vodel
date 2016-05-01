<?hh //strict
namespace Vodel;

class ClassUtil {



  public function isSubclass(string $child, string $parent):bool
  {
    $class = new \ReflectionClass($child);
    return $class->isSubclassOf($parent);
  }

  public function classExists(string $class):bool
  {
    return class_exists($class);
  }

  public function getReflection(string $class):\ReflectionClass
  {
    return new \ReflectionClass($class);
  }

}
