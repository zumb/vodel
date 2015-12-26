<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

abstract class RegExp implements Validator
{
  public static string $PATTERN = "";

  public function check(mixed $value):bool
  {
    if(is_string($value)) {
      return preg_match(static::$PATTERN, $value) == 1;
    }
    return false;
  }

  public function getErrorMessage():string
  {
    return "Value is does not match: ".static::$PATTERN;
  }

}
