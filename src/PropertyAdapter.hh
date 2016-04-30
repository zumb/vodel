<?hh //strict
namespace Vodel;

use Vodel\Interfaces\Validator;
use Vodel\Interfaces\TransformsData;
use Vodel\Interfaces\ComplexValidator;

class PropertyAdapter
{
  protected mixed $value;

  protected Vector<string> $failures = Vector {};

  public function __construct (
    protected string $name,
    protected string $type,
    public ?Validator $validator = null
  ) {}

  public function setValue(\ReflectionClass $jsonReflection, \stdClass $jsonObject):void
  {
    try {
      $this->value = $jsonReflection->getProperty($this->name)
        ->getValue($jsonObject);
    } catch (\ReflectionException $ex) {}
  }

  public function validate():bool
  {
    if($this->value == null) {
      return $this->isOptional();
    }elseif($this->validator !== null) {
      return $this->validator->validate($this->value);
    }
    return true;
  }

  public function isOptional():bool
  {
    return strpos($this->type, '?') === 0;
  }

  public function getFailure():mixed
  {
    if($this->value == null && !$this->isOptional()) {
      return "Required";
    } elseif($this->validator instanceof ComplexValidator) {
      return $this->validator->getFailures();
    } elseif($this->validator) {
      return $this->validator->getErrorMessage();
    }
  }

  public function getName():string
  {
    return $this->name;
  }

}
