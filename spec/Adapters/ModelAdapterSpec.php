<?hh //partial

namespace spec\Zumb\Vodel\Adapters;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Zumb\Vodel\Reflection\ClassAnalyzer;
use Zumb\Vodel\Interfaces\InputParameter;

class ModelAdapterSpec extends ObjectBehavior
{
  public function let($class, $property)
  {
    $property->beADoubleOf(InputParameter::class);
    $class->beADoubleOf(ClassAnalyzer::class);
    $this->beConstructedWith($class);
  }

  public function it_validates_without_validations($class, $property)
  {
    $class->getInputToValidate()
      ->willReturn([]);
    $this->validate(null)
      ->shouldReturn(true);
  }

  public function it_works_with_null_input($class, $property)
  {
    $property->isOptional()
      ->willReturn(false);
    $property->extractValue(Argument::any(), Argument::any())
      ->willThrow(\ReflectionException::class);
    $property->getName()
      ->willReturn("test");
    $class->getInputToValidate()
      ->willReturn([$property]);
    $this->validate(null)
      ->shouldReturn(false);
  }
}
