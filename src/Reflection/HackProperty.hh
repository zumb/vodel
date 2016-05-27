<?hh //strict
namespace Zumb\Vodel\Reflection;

class HackProperty
{
  public function __construct(
    protected \ReflectionProperty $property
  ) {}

  public function isNullable():bool
  {
    return strpos($this->property->getTypeText(), '?') === 0;
  }

  public function getProperty():\ReflectionProperty
  {
    return $this->property;
  }
}
