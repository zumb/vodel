<?hh //strict
namespace Vodel\Interfaces;

interface TypeChecker
{
  public function getType():string;

  public function check(mixed $value):bool;

}
