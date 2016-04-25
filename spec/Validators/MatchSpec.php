<?hh //partial

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

enum Color:string {
  RED = "red";
  WHITE = "white";
}

class MatchSpec extends ObjectBehavior
{
  public function let()
  {
    $this->beConstructedWith(new \ReflectionClass(Color::class));
  }

  public function it_validates_correct_value()
  {
      $this->validate("red")
        ->shouldReturn(true);
      $this->validate("white")
        ->shouldReturn(true);
  }

  public function it_validates_incorrect_value()
  {
      $this->validate("brown")
        ->shouldReturn(false);
  }
}
