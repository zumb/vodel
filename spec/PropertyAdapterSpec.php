<?php

namespace spec\Vodel;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Vodel\Interfaces\Validator;

class PropertyAdapterSpec extends ObjectBehavior
{
  function let($property, $inputProperty)
  {
    $inputProperty->beADoubleOf(\ReflectionProperty::class);
    $property->beADoubleOf(\ReflectionProperty::class);
    $this->beConstructedWith($property);
  }

  function it_detects_required_property($property)
  {
    $property->getTypeText()
      ->willReturn('HH\string');
    $this->isRequired()->shouldBe(true);
  }

  function it_detects_optional_property($property)
  {
    $property->getTypeText()
      ->willReturn('?HH\string');
    $this->isRequired()->shouldBe(false);
  }

  function it_checks_null_input($property)
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

  function it_checks_input_without_validator($inputProperty)
  {
    $this->validate($inputProperty)
      ->shouldBe(true);
  }

  function it_checks_input_with_validator($property, $inputProperty, $validator)
  {
    $validator->beADoubleOf(Validator::class);
    $this->beConstructedWith($property, $validator);
    $inputProperty->getValue()
      ->willReturn("value");
    $validator->validate("value")
      ->willReturn(true);
    $this->validate($inputProperty)
      ->shouldBe(true);
    $validator->validate("value")
      ->willReturn(false);
    $this->validate($inputProperty)
      ->shouldBe(false);
  }
}
