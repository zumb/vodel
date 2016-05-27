<?hh //partial

namespace spec\Zumb\Vodel\Adapters;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Zumb\Vodel\ValidationRepository;

class ModelAdapterSpec extends ObjectBehavior
{
  public function let($repository, $class)
  {
    $repository->beADoubleOf(ValidationRepository::class);
    $class->beADoubleOf(\ReflectionClass::class);
    $this->beConstructedWith($repository, $class);
  }

  public function it_fails_if_input_is_not_object()
  {
    $this->validate(null)
      ->shouldReturn(false);
  }
}
