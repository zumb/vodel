<?hh //strict
namespace Vodel;

use Vodel\Validators\ArrayValidator;
use Vodel\Interfaces\JsonModel;

class PropertyAdapterFactory
{
  public function __construct(
    protected ValidationRepository $validations
  ) {}

  public function make(\ReflectionProperty $property):PropertyAdapter
  {
    $validator = $this->validations->getValidatorFor($property);
    if($this->validations->isModel($property)) {
      $validator = new JsonModelAdapter($this, $property->getDeclaringClass());
    } elseif($validator !== null) {
      if($this->validations->isVector($property)) {
        $validator = new ArrayValidator($validator);
      }
    }
    return new PropertyAdapter($property, $validator);
  }

}
