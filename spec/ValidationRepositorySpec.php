<?php

namespace spec\Vodel;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Vodel\PropertyAdapterFactory;
use Vodel\ValidationRepository;
use Vodel\Interfaces\Validator;

class ValidationRepositorySpec extends ObjectBehavior
{

  function let($property, $class)
  {
    $property->beADoubleOf(\ReflectionProperty::class);
    $class->beADoubleOf(\ReflectionClass::class);
  }

  function it_checks_property_is_model($property, $class)
  {
    $class->implementsInterface(\Vodel\Interfaces\JsonModel::class)
    	->willReturn(true);
    $property->getDeclaringClass()
    	->willReturn($class);
    $this->isModel($property)->shouldReturn(true);
  }

  function it_checks_property_is_not_object($property)
  {
  	$property->getDeclaringClass()
  	 ->willReturn(null);
  	$this->isModel($property)->shouldReturn(false);
  }

  function it_checks_property_is_not_vector($property)
  {
  	$property->getDeclaringClass()
  	  ->willReturn(null);
  	$this->isVector($property)->shouldReturn(false);
  }

  function it_checks_property_is_vector($property)
  {
  	$property->getDeclaringClass()
  	 ->willReturn(new \ReflectionClass("hh\Vector"));
  	$this->isVector($property)->shouldReturn(true);
  }

  function it_checks_property_is_not_model($property, $class)
  {
  	$property->getDeclaringClass()
  	 ->willReturn(null);
  	$class->implementsInterface(\Vodel\Interfaces\JsonModel::class)
  	 ->willReturn(false);
  	$this->isModel($property)->shouldReturn(false);
  }

  function it_returns_exact_match_validator($property, $validator)
  {
    $property->getTypeText()->willReturn("Type");
    $validator->beADoubleOf(Validator::class);
    $this->addValidator("Type", $validator);
    $this->getValidatorFor($property)
      ->shouldReturn($validator);
  }

  function it_does_not_have_a_validator($property, $validator)
  {
    $property->getTypeText()->willReturn("AnotherType");
    $property->getDeclaringClass()->willReturn(null);
    $validator->beADoubleOf(Validator::class);
    $this->addValidator("Type", $validator);
    $this->getValidatorFor($property)
      ->shouldBe(null);
  }

  function it_returns_parent_match_validator($property, $class, $validator)
  {
    $property->getTypeText()->willReturn("SubType");
    $property->getDeclaringClass()->willReturn($class);
    $class->isSubclassOf("Type")->willReturn(true);
    $validator->beADoubleOf(Validator::class);
    $this->addValidator("Type", $validator);
    $this->getValidatorFor($property)
      ->shouldReturn($validator);
  }
}
