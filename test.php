<?hh //partial


enum Color: string {
  RED = "red";
  WHITE= "white";
}

class OtherClass {

}

class Test
{
  public ?string $optional;

  public Vector<string> $vector = Vector{};

  public Color $enum = Color::RED;

  public ?OtherClass $classProperty = null;
}

function main () {
  $reflection = new \ReflectionClass(Test::class);
  var_dump($reflection->getProperties() );
  var_dump($reflection->getProperty("enum")->getDeclaringClass());
  var_dump(new \ReflectionMethod("Color", "assert"));
  var_dump(new \ReflectionClass("Color"));
}
main();
