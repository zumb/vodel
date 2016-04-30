<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Enum implements Validator
{
  public function __construct(
    protected \ReflectionClass $enum
  ) {}

  public function validate(mixed $value):bool
  {
    if(is_string($value)) {
      $assert = $this->enum->getMethod("assert");
      try {
        $assert->invoke(null, $value);
        return true;
      } catch (\UnexpectedValueException $ex) {
        return false;
      }
    }
    return false;
  }

  public function getErrorMessage():string
  {
    return "Value should be in this list: ".
      implode(', ', $this->enum->getMethod("getNames")->invoke(null));
  }
}
