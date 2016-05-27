<?hh //partial

namespace spec\Zumb\Vodel\Adapters;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Zumb\Vodel\Interfaces\Validator;

class VectorAdapterSpec extends ObjectBehavior
{
  public function let($validator)
  {
    $validator->beADoubleOf(Validator::class);
    $this->beConstructedWith($validator);
  }

  public function it_fails_if_one_fails($validator)
  {
    $validator->getErrorMessage()
      ->willReturn("Error");
    $validator->validate(Argument::any())
      ->shouldBeCalledTimes(1)
      ->willReturn(false);
    $this->validate(["one", "two"])
      ->shouldReturn(false);
  }

  public function it_succeeds_if_all_succeeds($validator)
  {
    $validator->validate(Argument::any())
      ->shouldBeCalledTimes(2)
      ->willReturn(true);
    $this->validate(["one", "two"])
      ->shouldReturn(true);
  }

  public function it_fails_if_input_not_array($validator)
  {
    $this->validate("text")
      ->shouldReturn(false);
  }
}
