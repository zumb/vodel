<?php

namespace spec\Vodel;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Vodel\PropertyAdapterFactory;
use Vodel\PropertyAdapter;

class JsonModelAdapterSpec extends ObjectBehavior
{
  function let($factory, $model, $property, $adapter)
  {
      $factory->beADoubleOf(PropertyAdapterFactory::class);
      $model->beADoubleOf(\ReflectionClass::class);
      $property->beADoubleOf(\ReflectionProperty::class);
      $adapter->beADoubleOf(PropertyAdapter::class);
      $this->beConstructedWith($factory, $model);
  }

  function it_checks_input_is_object()
  {
    $this->validate("string")
      ->shouldBe(false);
  }

  function it_checks_input_properties($model, $property, $factory, $adapter)
  {
    $factory->make($property)
      ->shouldBeCalledTimes(2)
      ->willReturn($adapter);
    $adapter->validate(Argument::any())
      ->shouldBeCalledTimes(2)
      ->willReturn(true);
    $property->getName()
      ->willReturn("name", "last_name");
    $model->getProperties(\ReflectionProperty::IS_PUBLIC)
      ->willReturn([$property, $property]);
    $input = new \stdClass;
    $input->name = "test";
    $input->last_name = "second test";
    $this->validate($input)
      ->shouldBe(true);
  }

  function it_checks_input_properties_fails($model, $property, $factory, $adapter)
  {
    $factory->make($property)
      ->willReturn($adapter);
    $adapter->validate(Argument::any())
      ->willReturn(false);
    $property->getName()
      ->willReturn("name", "last_name");
    $model->getProperties(\ReflectionProperty::IS_PUBLIC)
      ->willReturn([$property, $property]);
    $input = new \stdClass;
    $input->name = "test";
    $input->last_name = "second test";
    $this->validate($input)
      ->shouldBe(false);
  }
}
