<?hh //strict
namespace Vodel\Input;

use Vodel\Interfaces\Validator;
use Vodel\Interfaces\JsonModel;

class SetterMethod extends InputParameterAbstract
{
  public function __construct(
    protected \ReflectionMethod $method,
    protected JsonModel $model,
    protected ?Validator $validator = null
  ) {
    $parameter = $method->getParameters()[0];
    parent::__construct(
      lcfirst(str_replace('set', '', $method->getName())),
      $parameter->isOptional(),
      $validator
    );
  }

  public function applyValue():void
  {
    $this->method->invoke($this->model, $this->getValue());
  }

}
