<?php

namespace spec\Vodel\Validators;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;

class UrlSpec extends ObjectBehavior
{
  function it_validates_correct_url()
  {
      $this->validate("http://google.com")
        ->shouldReturn(true);
  }

  function it_validates_incorrect_url()
  {
      $this->validate("http:google.com")
        ->shouldReturn(false);
  }
}
