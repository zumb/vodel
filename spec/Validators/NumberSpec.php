<?php

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class NumberSpec extends ObjectBehavior
{
    function it_validates_correct_value()
    {
        $this->validate(123)
          ->shouldReturn(true);
    }

    function it_validates_incorrect_value()
    {
        $this->validate("text")
          ->shouldReturn(false);
        $this->validate("123")
          ->shouldReturn(false);
    }
}