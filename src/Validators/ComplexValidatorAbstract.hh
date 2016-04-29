<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

abstract class ComplexValidatorAbstract implements Validator
{
  protected Vector<string> $failures = Vector {};

  public function getFailures():Vector<string>
  {
    return $this->failures;
  }
}
