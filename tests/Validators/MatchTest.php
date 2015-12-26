<?hh //decl
namespace Vodel\Tests\Validators;

use Vodel\Validators;

enum Role: string {
  USER = "user";
  ADMIN = "admin";
  EDITOR = "editor";
};

class EnumTest extends \PHPUnit_Framework_TestCase
{
  protected Role $property;

  public function testCheck()
  {
    $prop = new \ReflectionProperty($this, "property");
    $validator = new Validators\Match($prop->getTypeText());
    $this->assertTrue($validator->check("admin"));
    $this->assertFalse($validator->check(100));
    $this->assertFalse($validator->check("name"));
  }

  public function testErrorMessage()
  {
    $prop = new \ReflectionProperty($this, "property");
    $validator = new Validators\Match($prop->getTypeText());
    $this->assertNotEmpty($validator->getErrorMessage());
    $this->assertStringEndsWith(implode(", ", Role::getValues()), $validator->getErrorMessage());
  }

}
