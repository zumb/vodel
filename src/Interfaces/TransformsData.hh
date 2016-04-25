<?hh //strict
namespace Vodel\Interfaces;

interface TransformsData<Tf, Tt>
{
  public function transform(Tf $value):?Tt;
}
