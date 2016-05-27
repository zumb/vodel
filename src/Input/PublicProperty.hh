<?hh //strict
namespace Zumb\Vodel\Input;

use Zumb\Vodel\Interfaces\Validator;
use Zumb\Vodel\Reflection\HackProperty;
use Zumb\Vodel\Interfaces\JsonModel;

class PublicProperty extends InputParameterAbstract
{
  public function __construct(
    protected HackProperty $property,
    protected ?Validator $validator,
    protected JsonModel $model
  ) {
    parent::__construct(
      $property->getProperty()->getName(),
      $property->isNullable(),
      $validator
    );
  }

  public function applyValue():void
  {
    $this->property->getProperty()
      ->setValue($this->model, $this->getValue());
  }
}
