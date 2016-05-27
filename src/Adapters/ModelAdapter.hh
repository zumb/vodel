<?hh //strict
namespace Zumb\Vodel\Adapters;

use Zumb\Vodel\Interfaces\JsonModel;
use Zumb\Vodel\Interfaces\Validator;
use Zumb\Vodel\PropertyInspector;
use Zumb\Vodel\Interfaces\InputParameter;
use Zumb\Vodel\ValidationRepository;
use Zumb\Vodel\Reflection\ClassAnalyzer;

class ModelAdapter extends AdapterAbstract
{

  public function __construct(
    protected ClassAnalyzer $class
  ) {}

  public function validate(mixed $jsonObject):bool
  {
    if(!$jsonObject instanceof \stdClass) {
      $jsonObject = new \stdClass();
    }
    $jsonReflection = new \ReflectionClass($jsonObject);
    foreach($this->class->getInputToValidate() as $property) {
      try {
        $property->extractValue($jsonReflection, $jsonObject);
        if(!$property->validate()) {
          $this->addFailMessage($property->getName(), $property->getValidator());
        }
      } catch(\ReflectionException $ex) {
        if(!$property->isOptional()) {
          $this->failures->add(Pair{$property->getName(), "Required"});
        }
      }
    }
    return $this->failures->count() == 0;
  }

  public function getErrorMessage():string
  {
    return "Invalid input";
  }

}
