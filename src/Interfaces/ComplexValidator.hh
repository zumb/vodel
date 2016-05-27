<?hh //strict
namespace Zumb\Vodel\Interfaces;

interface ComplexValidator
{
  public function getFailures():Map<string, mixed>;
}
