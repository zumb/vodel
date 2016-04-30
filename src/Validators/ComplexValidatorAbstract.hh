<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\ComplexValidator;
use Vodel\Interfaces\Validator;

abstract class ComplexValidatorAbstract implements ComplexValidator
{
  protected Map<string, mixed> $failures = Map {};

  public function getFailures():Map<string, mixed>
  {
    return $this->failures;
  }

  public function addFailMessage(string $name, ?Validator $validator):void
  {
    if($validator instanceof ComplexValidator) {
      $this->failures->add(Pair{$name, $validator->getFailures()});
    } elseif($validator) {
      $this->failures->add(Pair{$name, $validator->getErrorMessage()});
    }
  }
}
