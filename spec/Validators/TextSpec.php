<?php

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class TextSpec extends ObjectBehavior
{
    function it_detects_text()
    {
      $this->validate("text")
        ->shouldReturn(true);
    }

    function it_detects_what_is_not_text()
    {
      $this->validate(123)
        ->shouldReturn(false);
    }

}
