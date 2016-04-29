<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class ArrayValidator extends ComplexValidatorAbstract
{
  public function __construct(
    protected Validator $validator
  ) {}

  public function validate(mixed $array):bool
  {
    if(is_array($array)) {
      foreach($array as $value) {
        if(!$this->validator->validate($value)) {
          $this->failures->addAll($this->validator->getFailures());
          return false;
        }
      }
      return true;
    }
    return false;
  }

}
