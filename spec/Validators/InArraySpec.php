<?hh //partial

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class InArraySpec extends ObjectBehavior
{
  public function let()
  {
    $this->beConstructedWith(["one", "two"]);
  }

  public function it_validates_correct_value()
  {
      $this->validate("one")
        ->shouldReturn(true);
      $this->validate("two")
        ->shouldReturn(true);
  }

  public function it_validates_incorrect_value()
  {
      $this->validate("three")
        ->shouldReturn(false);
  }
}
