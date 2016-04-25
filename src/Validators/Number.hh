<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Number implements Validator
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
