<?hh //strict
namespace Vodel;

class ErrorBag
{
  protected Map<string, mixed> $errors = Map{};

  public function add(string $property, mixed $errors):void
  {
    $this->errors->add(Pair{$property, $errors});
  }

}
