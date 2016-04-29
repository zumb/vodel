<?php

namespace spec\Vodel;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Vodel\Interfaces\Validator;

class PropertyAdapterSpec extends ObjectBehavior
{
  function let($property)
  {
    $property->beADoubleOf(\ReflectionProperty::class);
    $this->beConstructedWith($property);
  }

  function it_detects_required_property($property)
  {
    $property->getTypeText()
      ->willReturn('HH\string');
    $this->isOptional()->shouldBe(false);
  }

  function it_detects_optional_property($property)
  {
    $property->getTypeText()
      ->willReturn('?HH\string');
    $this->isOptional()->shouldBe(true);
  }

/*  function it_checks_null_input($property)
  {
    $property->getTypeText()
      ->willReturn('?HH\string');
    $this->validate(null)
      ->shouldBe(true);
    $property->getTypeText()
      ->willReturn('HH\string');
    $this->validate(null)
      ->shouldBe(false);
  }

  function it_checks_input_without_validator()
  {
    $this->validate("value")
      ->shouldBe(true);
  }

  function it_checks_input_with_validator($property, $validator)
  {
    $validator->beADoubleOf(Validator::class);
    $this->beConstructedWith($property, $validator);
    $validator->validate("value")
      ->willReturn(true);
    $this->validate("value")
      ->shouldBe(true);
    $validator->validate("value")
      ->willReturn(false);
    $this->validate("value")
      ->shouldBe(false);
  } */
}
