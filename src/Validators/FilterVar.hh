<?hh //strict
namespace Zumb\Vodel\Validators;

use Zumb\Vodel\Interfaces\Validator;

class FilterVar implements Validator
{
  public function __construct(
    protected int $flag,
    protected mixed $options = null
  ) {}

  public function validate(mixed $value):bool
  {
    if(is_string($value)){
      return filter_var($value, $this->flag, $this->options) !== false;
    }
    return false;
  }

  public function getErrorMessage():string
  {
    return "Invalid input for flag ".$this->flag;
  }
}
