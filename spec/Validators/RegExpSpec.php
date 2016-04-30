<?hh //partial

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class RegExpSpec extends ObjectBehavior
{
  public function let()
  {
    $this->beConstructedWith("/^[0-9]$/");
  }

  public function it_validates_correct_value()
  {
    $this->validate("5")
      ->shouldReturn(true);
  }

  public function it_validates_incorrect_value()
  {
    $this->validate("text")
      ->shouldReturn(false);
    $this->validate("12")
      ->shouldReturn(false);
  }
}
