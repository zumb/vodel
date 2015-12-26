<?hh //decl
namespace Vodel\Tests\Validators;

use Vodel\Validators;

type Role = string;

class RoleValidator extends Validators\InArray<string>
{
  protected array<string> $values = ["admin", "editor", "king"];
}

class InArrayTest extends \PHPUnit_Framework_TestCase
{
  protected Role $property = '';

  public function testCheck()
  {
    $validator = new RoleValidator();
    $this->assertTrue($validator->check("king"));
    $this->assertFalse($validator->check(100));
    $this->assertFalse($validator->check("name"));
  }

  public function testErrorMessage()
  {
    $validator = new RoleValidator();
    $this->assertNotEmpty($validator->getErrorMessage());
  }

}
