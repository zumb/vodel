<?php

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Vodel\Interfaces\Validator;

class ArrayValidatorSpec extends ObjectBehavior
{
  function let($validator)
  {
    $validator->beADoubleOf(Validator::class);
    $this->beConstructedWith($validator);
  }

  function it_fails_if_one_fails($validator)
  {
    $validator->validate(Argument::any())
      ->shouldBeCalledTimes(1)
      ->willReturn(false);
    $validator->getFailures()
      ->willReturn(new \HH\Vector());
    $this->validate(["one", "two"])
      ->shouldReturn(false);
  }

  function it_succeeds_if_all_succeeds($validator)
  {
    $validator->validate(Argument::any())
      ->shouldBeCalledTimes(2)
      ->willReturn(true);
    $this->validate(["one", "two"])
      ->shouldReturn(true);
  }

  function it_fails_if_input_not_array()
  {
    $this->validate("text")
      ->shouldReturn(false);
  }
}
