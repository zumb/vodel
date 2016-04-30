<?hh //strict
namespace Vodel;

use Vodel\Interfaces\Validator;
use Vodel\Interfaces\TransformsData;
use Vodel\Interfaces\ComplexValidator;

class PropertyAdapter
{
  protected Vector<string> $failures = Vector {};

  public function __construct (
    protected string $name,
    protected string $type,
    public ?Validator $validator = null
  ) {}

  public function extractValue(\ReflectionClass $jsonReflection, \stdClass $jsonObject):mixed
  {
    return $jsonReflection->getProperty($this->getName())
      ->getValue($jsonObject);
  }

  public function validate(mixed $value):bool
  {
    if($value == null) {
      return $this->isOptional();
    }elseif($this->validator !== null) {
      return $this->validator->validate($value);
    }
    return true;
  }

  public function isOptional():bool
  {
    return strpos($this->type, '?') === 0;
  }

  public function getValidator():?Validator
  {
    return $this->validator;
  }

  public function getName():string
  {
    return $this->name;
  }

}
