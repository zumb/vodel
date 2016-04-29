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
    $this->beConstructedWith('HH\Vector<array<string>>');
    $this->isVector()
      ->shouldReturn(true);
  }

  public function it_extracts_type_from_vector()
  {
    $this->beConstructedWith('HH\Vector<array<string>>');
    $this->getVectorType()
      ->shouldReturn('array<string>');
  }

  public function it_returns_type_for_nullable()
  {
    $this->beConstructedWith('?HH\string');
    $this->getBasicType()->shouldReturn('HH\string');
  }

  public function it_returns_type_for_subtyped()
  {
    $this->beConstructedWith('array<string>');
    $this->getBasicType()->shouldReturn('array');
  }

  public function it_detects_enum()
  {
    $this->beConstructedWith('spec\Vodel\EnumTest');
    $this->isEnum()->shouldReturn(true);
  }

  public function it_detects_not_enum()
  {
    $this->beConstructedWith('string');
    $this->isEnum()->shouldReturn(false);
  }
}
