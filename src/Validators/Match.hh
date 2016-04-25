<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Match implements Validator
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

}
