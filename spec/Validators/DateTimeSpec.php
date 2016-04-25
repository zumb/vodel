<?php

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class DateTimeSpec extends ObjectBehavior
{
  function let()
  {
    \Vodel\Validators\DateTime::$FORMAT = \DateTime::ISO8601;
  }

  function it_validates_correct_value()
  {
    $this->validate("1997-07-16T19:20:30+01:00")
      ->shouldReturn(true);
  }

  function it_validates_incorrect_value()
  {
      $this->validate("1997-16-07T19:20:30")
        ->shouldReturn(false);
  }

  function it_validates_custom_format()
  {
    \Vodel\Validators\DateTime::$FORMAT = "d-m-Y";
    $this->validate("1997-07-16T19:20:30+01:00")
      ->shouldReturn(false);
    $this->validate("16-07-1997")
      ->shouldReturn(true);
  }
}
