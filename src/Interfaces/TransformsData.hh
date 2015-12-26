<?hh //strict
namespace Vodel\Interfaces;

interface TransformsData<T>
{
  public function transform(mixed $value):?T;
}
