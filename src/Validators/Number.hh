<?hh //strict
namespace Zumb\Vodel\Validators;

use Zumb\Vodel\Interfaces\Validator;

class Number implements Validator
{
  public function validate(mixed $value):bool
  {
    return is_float($value);
  }

  public function getErrorMessage():string
  {
    return "Value must be an integer number";
  }
}
