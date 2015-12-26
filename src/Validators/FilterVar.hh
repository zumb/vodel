<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

abstract class FilterVar implements Validator
{
  public static int $FLAG = 0;

  public function check(mixed $value):bool
  {
    if(is_string($value)) {
      return filter_var($value, static::$FLAG) !== false;
    }
    return false;
  }

  public function getErrorMessage():string
  {
    return "Value does not match";
  }

}
