<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

abstract class InArray<T> implements Validator
{
  protected array<T> $values = [];

  public function check(mixed $value):bool
  {
    return in_array($value, $this->values, true);
  }

  public function getErrorMessage():string
  {
    return "Value must be one of this: ".implode(", ", $this->values);
  }

}
