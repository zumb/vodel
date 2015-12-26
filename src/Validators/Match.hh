<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Match<T> implements Validator
{
  public function __construct(
    protected classname<T> $enum
  ) {}

  public function check(mixed $value):bool
  {
    $assert = new \ReflectionMethod($this->enum, "assert");
    try {
      $assert->invoke(null, $value);
      return true;
    } catch (\UnexpectedValueException $ex) {
      return false;
    }
  }

  public function getErrorMessage():string
  {
    $getNames = new \ReflectionMethod($this->enum, "getValues");
    return "Value must be one of: ".implode(", ", $getNames->invoke(null));
  }

}
