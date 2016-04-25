<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Text implements Validator
{
  public function validate(mixed $value):bool
  {
    return is_string($value);
  }
}
