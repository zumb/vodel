<?hh // partial

namespace spec\Vodel;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

enum EnumTest: string {
  ONE = "one";
}

class PropertyInspectorSpec extends ObjectBehavior
{
  public function it_detects_vector()
  {
    $this->isVector('HH\Vector<array<string>>')
      ->shouldReturn(true);
  }

  public function it_extracts_type_from_vector()
  {
    $this->getVectorType('HH\Vector<array<string>>')
      ->shouldReturn('array<string>');
  }

  public function it_returns_type_for_nullable()
  {
    $this->getBasicType('?HH\string')
      ->shouldReturn('HH\string');
  }

  public function it_returns_type_for_subtyped()
  {
    $this->getBasicType('array<string>')
      ->shouldReturn('array');
  }

  public function it_detects_enum()
  {
    $this->isEnum('spec\Vodel\EnumTest')
      ->shouldReturn(true);
  }

  public function it_detects_not_enum()
  {
    $this->isEnum('string')
      ->shouldReturn(false);
  }
}
