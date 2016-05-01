<?hh //partial

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class NumberSpec extends ObjectBehavior
{
  public function it_validates_correct_value()
  {
    $this->validate(123.00)
      ->shouldReturn(true);
  }

  public function it_validates_incorrect_value()
  {
    $this->validate("text")
      ->shouldReturn(false);
    $this->validate("123")
      ->shouldReturn(false);
  }
}
