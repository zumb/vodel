<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class InArray<T> implements Validator
{
  public function __construct(
    protected array<T> $values
  ) {}

  public function validate(mixed $value):bool
  {
    return in_array($value, $this->values, true);
  }

  public function getErrorMessage():string
  {
    return "Value should be one of these: ".implode(",", $this->values);
  }
}
