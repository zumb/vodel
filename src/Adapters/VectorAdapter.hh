<?hh //strict
namespace Zumb\Vodel\Adapters;

use Zumb\Vodel\Interfaces\Validator;
use Zumb\Vodel\Interfaces\Adapter;
use Zumb\Vodel\Interfaces\TransformsData;

class VectorAdapter extends AdapterAbstract implements
  Validator,
  TransformsData<array<mixed>, Vector<mixed>>
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

  public function transform(array<mixed> $input):Vector<mixed>
  {
    $vector = Vector{};
    foreach($input as $item) {
      if($this->validator instanceof TransformsData) {
        $vector->add($this->validator->transform($item));
      } else {
        $vector->add($item);
      }
    }
    return $vector;
  }
}
