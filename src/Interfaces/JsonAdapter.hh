<?hh //strict
namespace Vodel\Interfaces;

interface JsonAdapter
{

  public function getErrors():Vector<string>;

  public function validate(\stdClass $jsonObject):bool;

  public function fillWith(\stdClass $jsonObject):void;

}
