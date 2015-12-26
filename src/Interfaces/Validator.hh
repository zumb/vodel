<?hh //strict
namespace Vodel\Interfaces;

interface Validator
{
  public function check(mixed $value):bool;

  public function getErrorMessage():string;
}
