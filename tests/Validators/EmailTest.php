<?hh //decl
namespace Vodel\Tests\Validators;

use Vodel\Validators;

class EmailTest extends \PHPUnit_Framework_TestCase
{

  protected \Vodel\Email $property = '';

  public function testGetType()
  {
    $prop = new \ReflectionProperty($this, "property");
    $validator = new Validators\Email();
    $this->assertEquals($prop->getTypeText(), $validator->getTarget());
  }

  public function testCheck()
  {
    $validator = new Validators\Email();
    $this->assertTrue($validator->check("name@email.com"));
    $this->assertFalse($validator->check(100));
    $this->assertFalse($validator->check("name"));
  }

  public function testErrorMessage()
  {
    $validator = new Validators\Email();
    $this->assertNotEmpty($validator->getErrorMessage());
  }

}
