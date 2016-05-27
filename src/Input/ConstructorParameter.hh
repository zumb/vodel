<?hh //strict
namespace Zumb\Vodel\Input;

use Zumb\Vodel\Interfaces\Validator;

class ConstructorParameter extends InputParameterAbstract
{
  public function __construct(
    protected \ReflectionParameter $parameter,
    protected ?Validator $validator,
    protected Map<string, mixed> $constructorAttrs
  ) {
    parent::__construct(
      $parameter->getName(),
      $parameter->isOptional(),
      $validator
    );
  }

  public function applyValue():void
  {
    $this->constructorAttrs->set($this->getName(), $this->getValue());
  }
}
