<?hh //partial

namespace spec\Vodel\Reflection;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

enum TestEnum:string {
  ONE = "one";
}

class TypeInspectorSpec extends ObjectBehavior
{
  public function it_detects_vector()
  {
    $this->isVector('?HH\Vector<string>')
      ->shouldReturn(true);
    $this->isVector('?HH\int')
      ->shouldReturn(false);
  }

  public function it_extracts_subtype()
  {
    $this->getSubType('?HH\Vector<array<string>>')
      ->shouldReturn('array<string>');
  }

  public function it_extracts_basic_type()
  {
    $this->getBasicType('?HH\Vector<array<string>>')
      ->shouldReturn('HH\Vector');
  }

  public function it_detects_enum()
  {
    $this->isEnum('spec\Vodel\Reflection\TestEnum')
      ->shouldReturn(true);
    $this->isEnum('HH\string')
      ->shouldReturn(false);
  }
}
