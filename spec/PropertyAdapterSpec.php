<?hh //partial

namespace spec\Vodel;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Vodel\Interfaces\Validator;

class PropertyAdapterSpec extends ObjectBehavior
{
  public function it_validates_null_when_optional()
  {
    $this->beConstructedWith('test', '?HH\string');
    $this->validate(null)
      ->shouldBe(true);
  }

  public function it_validates_null_when_required()
  {
    $this->beConstructedWith('test', 'HH\string');
    $this->validate(null)
      ->shouldBe(false);
  }

  public function it_checks_input_without_validator()
  {
    $this->beConstructedWith('test', 'HH\string');
    $this->validate("value")
      ->shouldBe(true);
  }

  public function it_succeeds_if_validator_succeeds($validator)
  {
    $validator->beADoubleOf(Validator::class);
    $this->beConstructedWith("test", 'HH\string', $validator);
    $validator->validate("value")
      ->willReturn(true);
    $this->validate("value")
      ->shouldBe(true);
  }

  public function it_fails_if_validator_fails($validator)
  {
    $validator->beADoubleOf(Validator::class);
    $this->beConstructedWith("test", 'HH\string', $validator);
    $validator->validate("value")
      ->willReturn(false);
    $this->validate("value")
      ->shouldBe(false);
  }
}
