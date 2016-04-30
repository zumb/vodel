<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\JsonModel;
use Vodel\Interfaces\Validator;
use Vodel\ValidationCollection;
use Vodel\Validators\ComplexValidatorAbstract;
use Vodel\PropertyInspector;
use Vodel\JsonModelAdapter;

class Model extends ComplexValidatorAbstract implements Validator
{
  protected Map<string, mixed> $failures = Map{};

  public function __construct(
    public JsonModelAdapter $model
  ) {}

  public function validate(mixed $jsonObject):bool
  {
    if($jsonObject instanceof \stdClass) {
      $jsonReflection = new \ReflectionClass($jsonObject);
      foreach($this->model->getPropertiesToValidate() as $property) {
        try {
          if(!$property->validate($property->extractValue($jsonReflection, $jsonObject))) {
            $this->addFailMessage($property->getName(), $property->getValidator());
          }
        } catch(\ReflectionException $ex) {
          if(!$property->isOptional()) {
            $this->failures->add(Pair{$property->getName(), "Required"});
          }
        }
      }
    }
    return $this->failures->count() == 0;
  }

  public function getErrorMessage():string
  {
    return "Invalid object";
  }
}
