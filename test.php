<?hh //partial

enum Color: string {
  RED = "red";
  WHITE= "white";
}

class Test
{
  public ?string $optional;

  public Vector<string> $vector = Vector{};

  public Color $enum = Color::RED;
}

function main () {
  $reflection = new \ReflectionClass(Test::class);
  var_dump($reflection->getProperties() );
  var_dump($reflection->getProperty("enum")->getDeclaringClass());
}
main();
