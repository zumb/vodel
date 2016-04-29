<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class RegExp implements Validator
{
  public function __construct(
    public string $expression
  ){}

  public function validate(mixed $value):bool
  {
    if(is_string($value)) {
      return preg_match($this->expression, $value) == 1;
    }
    return false;
  }

  public function getFailures():Vector<string>
  {
    return Vector{"Value does not match the expression: ".$this->expression};
  }

}
