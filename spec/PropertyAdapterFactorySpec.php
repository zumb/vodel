<?php

namespace spec\Vodel;

use PhpSpec\ObjectBehavior;
use Vodel\ValidationRepository;
use Vodel\Interfaces\Validator;
use Vodel\PropertyAdapter;
use Vodel\JsonModelAdapter;
use Vodel\Validators\ArrayValidator;

class PropertyAdapterFactorySpec extends ObjectBehavior
{
	function let($validations, $property, $validator, $class)
	{
		$validations->beADoubleOf(ValidationRepository::class);
		$property->beADoubleOf(\ReflectionProperty::class);
		$validator->beADoubleOf(Validator::class);
		$class->beADoubleOf(\ReflectionClass::class);
		$this->beConstructedWith($validations);
	}

	function it_returns_model_adapter($property, $validations, $validator, $class)
	{
		$property->getDeclaringClass()->willReturn($class);
		$validations->getValidatorFor($property)
			->wilLReturn($validator);
		$validations->isModel($property)
			->willReturn(true);
		$adapter = $this->make($property);
		$adapter->shouldReturnAnInstanceOf(PropertyAdapter::class);
		$adapter->shouldPass(function ($subject) use ($validator) {
			return $subject->validator instanceof JsonModelAdapter;
		});
	}

	function it_returns_original_validator($property, $validations, $validator, $class)
	{
		$validations->getValidatorFor($property)
			->wilLReturn($validator);
		$validations->isModel($property)
			->willReturn(false);
		$validations->isVector($property)
			->willReturn(false);
		$adapter = $this->make($property);
		$adapter->shouldReturnAnInstanceOf(PropertyAdapter::class);
		$adapter->shouldPass(function ($subject) use ($validator) {
			return $subject->validator == $validator->getWrappedObject();
		});
	}

	function it_returns_array_validator($property, $validations, $validator, $class)
	{
		$validations->getValidatorFor($property)
			->wilLReturn($validator);
		$validations->isModel($property)
			->willReturn(false);
		$validations->isVector($property)
			->willReturn(true);
		$adapter = $this->make($property);
		$adapter->shouldReturnAnInstanceOf(PropertyAdapter::class);
		$adapter->shouldPass(function ($subject) use ($validator) {
			return $subject->validator instanceof ArrayValidator;
		});
	}

	function getMatchers()
  {
    return [
        'pass' => function ($subject, $callback) {
          return $callback($subject);
        }
      ];
  }
}
