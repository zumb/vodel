<?hh //partial

namespace spec\Zumb\Vodel;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Zumb\Vodel\ValidationRepository;
use Zumb\Vodel\Interfaces\Validator;
use Zumb\Vodel\Reflection\TypeInspector;
use Zumb\Vodel\Validators;
use Zumb\Vodel\ClassUtil;
use Zumb\Vodel\Adapters;

class ValidationRepositorySpec extends ObjectBehavior
{
  public function let($inspector, $class, $util)
  {
    $inspector->beADoubleOf(TypeInspector::class);
    $class->beADoubleOf(\ReflectionClass::class);
    $util->beADoubleOf(ClassUtil::class);
    $this->beConstructedWith($util, $inspector);
  }

  public function it_returns_validator_for_model($inspector, $class, $util)
  {
    $util->getReflection("ModelClass")
      ->willReturn($class);
    $inspector->isModel("ModelClass")
      ->willReturn(true);
    $this->getValidatorFor("ModelClass")
      ->shouldBeAnInstanceOf(Adapters\ModelAdapter::class);
  }

  public function it_returns_validator_for_enum($inspector, $class, $util)
  {
    $inspector->isModel("Enum")
      ->willReturn(false);
    $inspector->isEnum("Enum")
      ->willReturn(true);
    $util->getReflection("Enum")
      ->willReturn($class);
    $this->getValidatorFor("Enum")
      ->shouldBeAnInstanceOf(Validators\Enum::class);
  }
}
