<?hh //strict
namespace Vodel;

use Vodel\Interfaces\Validator;
use Vodel\Validators\ComplexValidatorAbstract;
use Vodel\Interfaces\TransformsData;

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
    if($this->value == null && !$this->isOptional()) {
      $this->failures->add("Required");
      return false;
    }elseif($this->value) {
      if($this->validator instanceof TransformsData) {
        $this->value = $this->validator->transform($this->value);
      }
      if($this->validator !== null) {
        $result = $this->validator->validate($this->value);
        if(!$result && $this->validator != null) {
          $failures = $this->validator->getFailures();
          $this->failures->addAll($failures);
          return false;
        }
      }
    }
    return true;
  }

  public function isOptional():bool
  {
    return strpos($this->type, '?') === 0;
  }

  public function getFailures():Vector<string>
  {
    return $this->failures;
  }

  public function getName():string
  {
    return $this->name;
  }

}
