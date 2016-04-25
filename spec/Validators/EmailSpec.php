<?php

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class EmailSpec extends ObjectBehavior
{
  function it_validates_correct_value()
  {
      $this->validate("full+name@server-domain.com.ext")
        ->shouldReturn(true);
  }

  function it_validates_incorrect_value()
  {
      $this->validate("@server-domain.com.ext")
        ->shouldReturn(false);
  }
}
