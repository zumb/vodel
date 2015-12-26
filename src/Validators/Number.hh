<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Number implements Validator
{
  public function getTarget():string
  {
    return 'HH\int';
  }

  public function check(mixed $value):bool
  {
    return is_int($value);
  }

  public function getErrorMessage():string
  {
    return "Value must be an integer number";
  }
}
