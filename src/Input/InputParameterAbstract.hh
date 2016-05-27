<?hh // strict
namespace Zumb\Vodel\Input;

use Zumb\Vodel\Interfaces\InputParameter;
use Zumb\Vodel\Interfaces\Validator;
use Zumb\Vodel\Interfaces\TransformsData;

abstract class InputParameterAbstract implements InputParameter
{
  protected mixed $value;

  public function __construct(
    protected string $name,
    protected bool $optional,
    protected ?Validator $validator = null
  ) {}

  public function extractValue(\ReflectionClass $jsonReflection, \stdClass $jsonObject):mixed
  {
    $this->value = $jsonReflection->getProperty($this->getName())
      ->getValue($jsonObject);
    return $this->value;
  }

  public function getValue():mixed
  {
    if($this->validator instanceof TransformsData) {
      return $this->validator->transform($this->value);
    }
    return $this->value;
  }

  public function validate():bool
  {
    if($this->value == null) {
      return $this->optional;
    }elseif($this->validator !== null) {
      return $this->validator->validate($this->value);
    }
    return true;
  }

  public function getName():string
  {
    return $this->name;
  }

  public function isOptional():bool
  {
    return $this->optional;
  }

  public function getValidator():?Validator
  {
    return $this->validator;
  }
}
