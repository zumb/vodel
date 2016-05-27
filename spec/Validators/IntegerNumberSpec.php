<?hh //partial

namespace spec\Zumb\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class IntegerNumberSpec extends ObjectBehavior
{
  public function it_validates_int()
  {
    $this->validate(10)
      ->shouldReturn(true);
  }

  public function it_validates_other()
  {
    $this->validate(100.50)
      ->shouldReturn(false);
    $this->validate("100.50")
      ->shouldReturn(false);
  }
}
