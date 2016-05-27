<?hh //strict
namespace Zumb\Vodel\Validators;

use Zumb\Vodel\Interfaces\Validator;

class IntegerNumber implements Validator
{
  public function validate(mixed $value):bool
  {
    return is_int($value);
  }

  public function getErrorMessage():string
  {
    return "Value must be an integer number";
  }
}
