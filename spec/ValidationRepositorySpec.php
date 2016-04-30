<?hh //partial

namespace spec\Vodel;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Vodel\ValidationRepository;
use Vodel\Interfaces\Validator;
use Vodel\PropertyInspector;
use Vodel\Validators;

class ValidationRepositorySpec extends ObjectBehavior
{
  public function let($inspector, $class)
  {
    $inspector->beADoubleOf(PropertyInspector::class);
    $class->beADoubleOf(\ReflectionClass::class);
    $this->beConstructedWith($inspector);
  }

  public function it_returns_validator_for_model($inspector, $class)
  {
    $inspector->getReflectionClass("ModelClass")
      ->willReturn($class);
    $inspector->isModel("ModelClass")
      ->willReturn(true);
    $this->getValidatorFor("ModelClass")
      ->shouldBeAnInstanceOf(Validators\Model::class);
  }

  public function it_returns_validator_for_enum($inspector, $class)
  {
    $inspector->isModel("Enum")
      ->willReturn(false);
    $inspector->isEnum("Enum")
      ->willReturn(true);
    $inspector->getReflectionClass("Enum")
      ->willReturn($class);
    $this->getValidatorFor("Enum")
      ->shouldBeAnInstanceOf(Validators\Enum::class);
  }
}
