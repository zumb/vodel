<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class ArrayValidator extends ComplexValidatorAbstract implements Validator
{
  public function __construct(
    protected Validator $validator
  ) {}

  public function validate(mixed $array):bool
  {
    if(is_array($array)) {
      foreach($array as $index => $value) {
        if(!$this->validator->validate($value)) {
          $this->addFailMessage("Position {$index}", $this->validator);
          return false;
        }
      }
      return true;
    }
    return false;
  }

  public function getErrorMessage():string
  {
    return "Should be an array";
  }
}
