<?hh //strict
namespace Vodel\Interfaces;

interface ComplexValidator
{
  public function getFailures():Map<string, mixed>;
}
