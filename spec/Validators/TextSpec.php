<?hh //partial

namespace spec\Zumb\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class TextSpec extends ObjectBehavior
{
  public function it_detects_text()
  {
    $this->validate("text")
      ->shouldReturn(true);
  }

  public function it_detects_what_is_not_text()
  {
    $this->validate(123)
      ->shouldReturn(false);
  }

}
