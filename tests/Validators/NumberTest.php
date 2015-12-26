<?hh //decl
namespace Vodel\Tests\Validators;

use Vodel\Validators;

class NumberTest extends \PHPUnit_Framework_TestCase
{

  protected int $property = 0;

  public function testGetType()
  {
    $prop = new \ReflectionProperty($this, "property");
    $validator = new Validators\Number();
    $this->assertEquals($prop->getTypeText(), $validator->getTarget());
  }

  public function testCheck()
  {
    $validator = new Validators\Number();
    $this->assertFalse($validator->check("text"));
    $this->assertTrue($validator->check(100));
    $this->assertTrue($validator->check(100.50));
  }

  public function testErrorMessage()
  {
    $validator = new Validators\Number();
    $this->assertNotEmpty($validator->getErrorMessage());
  }

}
