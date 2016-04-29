<?hh //strict
namespace Vodel;

use Vodel\Interfaces\Validator;
use Vodel\Interfaces\JsonModel;
use Vodel\Validators;

class ValidationRepository
{
  protected Map<string, Validator> $validators = Map{};

  public function __construct(
    protected PropertyInspector $inspector
  ) {
    $this->addValidator('Vodel\Email', new Validators\Email());
    $this->addValidator('Vodel\Url', new Validators\Url());
    $this->addValidator('DateTime', new Validators\DateTime());
    $this->addValidator('HH\string', new Validators\Text());
    $this->addValidator('HH\int', new Validators\Number());
  }

  public function addValidator(string $target, Validator $validator):this
  {
    $this->validators->set($target, $validator);
    return $this;
  }

  public function getValidatorFor(string $typeText):?Validator
  {
    if($this->inspector->isModel($typeText)) {
      return new Validators\Model(
        new JsonModelAdapter($this, $this->inspector->getReflectionClass($typeText))
      );
    } elseif($this->inspector->isEnum($typeText)) {
      return new Validators\Enum($this->inspector->getReflectionClass($typeText));
    } elseif($this->inspector->isVector($typeText)) {
        $validator = $this->getValidatorFor($this->inspector->getVectorType($typeText));
        if($validator) {
          return new Validators\ArrayValidator($validator);
        }
    } else {
      return $this->getValidatorForClass($this->inspector->getBasicType($typeText));
    }
    return null;
  }

  public function getValidatorForClass(string $class):?Validator
  {
    if($this->validators->get($class)) {
      return $this->validators->get($class);
    } elseif($this->inspector->classExists($class)) {
      foreach($this->validators as $classTarget => $validator) {
        if($this->inspector->isSubclass($class, $classTarget)) {
          return $validator;
        }
      }
    }
    return null;
  }

}
