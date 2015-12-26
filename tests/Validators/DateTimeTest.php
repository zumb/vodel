<?hh //decl
namespace Vodel\Tests\Validators;

use Vodel\Validators;

class DateTimeTest extends \PHPUnit_Framework_TestCase
{
  protected \DateTime $property;

  public function testGetType()
  {
    $prop = new \ReflectionProperty($this, "property");
    $validator = new Validators\DateTime();
    $this->assertEquals($prop->getTypeText(), $validator->getTarget());
  }

  public function testCheck()
  {
    $validator = new Validators\DateTime();
    $this->assertTrue($validator->check("2015-01-01T12:00:00+00:00"));
    $this->assertFalse($validator->check(100));
    $this->assertFalse($validator->check("name"));
  }

  public function testErrorMessage()
  {
    $validator = new Validators\DateTime();
    $this->assertNotEmpty($validator->getErrorMessage());
  }

}
