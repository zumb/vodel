<?hh //strict
namespace Vodel\Interfaces;

interface InputParameter
{
  public function applyValue():void;

  public function extractValue(\ReflectionClass $jsonReflection, \stdClass $jsonObject):mixed;

  public function validate():bool;

  public function getName():string;

  public function isOptional():bool;

  public function getValidator():?Validator;

  public function getValue():mixed;
}
