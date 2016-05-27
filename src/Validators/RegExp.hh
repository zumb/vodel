<?hh //strict
namespace Zumb\Vodel\Validators;

use Zumb\Vodel\Interfaces\Validator;

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

  public function getErrorMessage():string
  {
    return "Value does not match the expression: ".$this->expression;
  }

}
