<?php

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class FilterVarSpec extends ObjectBehavior
{
  function let()
  {
    $this->beConstructedWith(FILTER_VALIDATE_IP, FILTER_FLAG_IPV4);
  }

  function it_validates_correct_value()
  {
    $this->validate("192.161.1.1")
      ->shouldReturn(true);
  }

  function it_validates_incorrect_value()
  {
    $this->validate("192.161.1")
      ->shouldReturn(false);
    $this->validate("2001:0db8:0000:0042:0000:8a2e:0370:7334")
      ->shouldReturn(false);
  }
}
