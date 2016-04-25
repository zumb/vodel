<?php

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class RegExpSpec extends ObjectBehavior
{
  function let()
  {
    $this->beConstructedWith("/^[0-9]$/");
  }

  function it_validates_correct_value()
  {
      $this->validate("5")
        ->shouldReturn(true);
  }

  function it_validates_incorrect_value()
  {
      $this->validate("text")
        ->shouldReturn(false);
      $this->validate("12")
        ->shouldReturn(false);
  }
}
