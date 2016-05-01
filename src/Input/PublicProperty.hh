<?hh //strict
namespace Vodel\Input;

use Vodel\Interfaces\Validator;
use Vodel\Reflection\HackProperty;
use Vodel\Interfaces\JsonModel;

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
