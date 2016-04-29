<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

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

  public function getFailures():Vector<string>
  {
    return Vector{"Invalid input for ".$this->flag};
  }
}
