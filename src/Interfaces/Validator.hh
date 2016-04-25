<?hh //strict
namespace Vodel\Interfaces;

interface Validator
{
  public function validate(mixed $value):bool;
}
