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
  protected Vector<string> $failures = Vector{};

  public function __construct(
    public JsonModelAdapter $model
  ) {}

  public function validate(mixed $jsonObject):bool
  {
    if($jsonObject instanceof \stdClass) {
      $jsonReflection = new \ReflectionClass($jsonObject);
      foreach($this->model->getPropertiesToValidate() as $property) {
        $property->setValue($jsonReflection, $jsonObject);
        if(!$property->validate()) {
          $this->failures->add($property->getName());
          $this->failures->addAll($property->getFailures());
          return false;
        }
      }
      return true;
    }
    return false;
  }

  public function getFailures():Vector<string>
  {
    return $this->failures;
  }
}
