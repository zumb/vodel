<?hh //strict
namespace Zumb\Vodel\Interfaces;

interface TransformsData<Tf, Tt>
{
  public function transform(Tf $value):?Tt;
}
