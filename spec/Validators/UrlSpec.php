<?hh //partial

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class UrlSpec extends ObjectBehavior
{
  public function it_validates_correct_url()
  {
    $this->validate("http://google.com")
      ->shouldReturn(true);
  }

  public function it_validates_incorrect_url()
  {
    $this->validate("http:google.com")
      ->shouldReturn(false);
  }
}
