<?hh //strict
namespace Zumb\Vodel;

use Zumb\Vodel\Interfaces\Validator;
use Zumb\Vodel\Interfaces\JsonModel;
use Zumb\Vodel\Validators;
use Zumb\Vodel\Reflection\TypeInspector;
use Zumb\Vodel\Reflection\ClassAnalyzer;

class ValidationRepository
{
  protected Map<string, Validator> $validators = Map{};

  public function __construct(
    protected ClassUtil $classUtil,
    protected TypeInspector $inspector
  ) {
    $this->addValidator('Email', new Validators\Email());
    $this->addValidator('Url', new Validators\Url());
    $this->addValidator('DateTime', new Validators\DateTime());
    $this->addValidator('HH\string', new Validators\Text());
    $this->addValidator('HH\float', new Validators\Number());
    $this->addValidator('HH\int', new Validators\IntegerNumber());
  }

  public function addValidator(string $target, Validator $validator):this
  {
    $this->validators->set($target, $validator);
    return $this;
  }

  public function getValidatorForClass(string $class):?Validator
  {
    if($this->validators->get($class)) {
      return $this->validators->get($class);
    } elseif($this->classUtil->classExists($class)) {
      foreach($this->validators as $classTarget => $validator) {
        if($this->classUtil->isSubclass($class, $classTarget)) {
          return $validator;
        }
      }
    }
    return null;
  }

  public function getValidatorFor(string $type):?Validator
  {
    if($this->inspector->isModel($type)) {
      return new Adapters\ModelAdapter(new ClassAnalyzer($this, $this->classUtil->getReflection($type)));
    } elseif($this->inspector->isEnum($type)) {
      return new Validators\Enum($this->classUtil->getReflection($type));
    } elseif($this->inspector->isVector($type)) {
        $validator = $this->getValidatorFor($this->inspector->getSubType($type));
        if($validator) {
          return new Adapters\VectorAdapter($validator);
        }
    } else {
      return $this->getValidatorForClass($this->inspector->getBasicType($type));
    }
    return null;
  }

}
