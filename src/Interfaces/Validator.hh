<?hh //strict
namespace Zumb\Vodel\Interfaces;

interface Validator
{
  public function validate(mixed $value):bool;

  public function getErrorMessage():string;
}
