<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Text implements Validator
{
  public function getTarget():string
  {
    return 'HH\string';
  }

  public function check(mixed $value):bool
  {
    return is_string($value);
  }

  public function getErrorMessage():string
  {
    return "Property is not a string";
  }

}
