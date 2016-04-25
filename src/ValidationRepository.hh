<?hh //strict
namespace Vodel;

use Vodel\Interfaces\Validator;
use Vodel\Interfaces\JsonModel;

class ValidationRepository
{
  protected Map<string, Validator> $validators = Map{};

  public function addValidator(string $target, Validator $validator):this
  {
    $this->validators->set($target, $validator);
    return $this;
  }

  public function getValidatorFor(\ReflectionProperty $property):?Validator
  {
    if($this->validators->get($property->getTypeText())) {
      return $this->validators->get($property->getTypeText());
    } elseif($property->getDeclaringClass()) {
      foreach($this->validators as $classTarget => $validator) {
        if($property->getDeclaringClass()->isSubclassOf($classTarget)) {
          return $validator;
        }
      }
    }
    return null;
  }

  public function isModel(\ReflectionProperty $property):bool
  {
    if($property->getDeclaringClass()) {
      return $property->getDeclaringClass()
        ->implementsInterface(JsonModel::class);
    }
    return false;
  }

  public function isVector(\ReflectionProperty $property):bool
  {
    if($property->getDeclaringClass()) {
      return strpos('HH\Vector', $property->getDeclaringClass()->getName()) == 0;
    }
    return false;
  }
}
