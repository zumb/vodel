<?hh //strict
namespace Vodel;

use Vodel\Interfaces\Validator;

class PropertyAdapter
{
  public function __construct (
    protected \ReflectionProperty $property,
    public ?Validator $validator = null
  ) {}

  public function validate(?\ReflectionProperty $inputProperty):bool
  {
    if($inputProperty != null) {
      if($this->validator !== null) {
        return $this->validator->validate($inputProperty->getValue());
      }
      return true;
    }
    return !$this->isRequired();
  }

  public function isRequired():bool
  {
    return strpos($this->property->getTypeText(), '?') !== 0;
  }

}
