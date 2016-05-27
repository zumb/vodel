<?hh //strict
namespace Zumb\Vodel\Adapters;

use Zumb\Vodel\Interfaces\Validator;

abstract class AdapterAbstract implements Validator
{
  protected Map<string, mixed> $failures = Map {};

  public function getFailures():Map<string, mixed>
  {
    return $this->failures;
  }

  public function addFailMessage(string $name, ?Validator $validator):void
  {
    if($validator instanceof AdapterAbstract) {
      $this->failures->add(Pair{$name, $validator->getFailures()});
    } elseif($validator) {
      $this->failures->add(Pair{$name, $validator->getErrorMessage()});
    }
  }
}
