<?hh //strict
namespace Vodel\Interfaces;

interface JsonAdapter
{

  public function getErrors():Vector<string>;

  public function validate(\ReflectionClass $jsonObject):bool;

  public function fillWith(\stdClass $jsonObject):void;

}
