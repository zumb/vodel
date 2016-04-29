<?hh //partial

namespace spec\Vodel;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Vodel\ValidationRepository;
use Vodel\Interfaces\Validator;
use Vodel\PropertyInspector;
use Vodel\JsonModelAdapter;
use Vodel\Validators;

class ValidationRepositorySpec extends ObjectBehavior
{
  public function let($property, $class)
  {
    $property->beADoubleOf(PropertyInspector::class);
    $class->beADoubleOf(\ReflectionClass::class);
  }

  public function it_returns_validator_for_model($property, $class)
  {
    $property->isModel()
      ->willReturn(true);
    $property->getReflectionClass()
      ->wilLReturn($class);
    $this->getValidatorFor($property)
      ->shouldBeAnInstanceOf(JsonModelAdapter::class);
  }

  public function it_returns_validator_for_enum($property, $class)
  {
    $property->isModel()
      ->willReturn(false);
    $property->isEnum()
      ->willReturn(true);
    $property->getReflectionClass()
      ->wilLReturn($class);
    $this->getValidatorFor($property)
      ->shouldBeAnInstanceOf(Validators\Enum::class);
  }
}
