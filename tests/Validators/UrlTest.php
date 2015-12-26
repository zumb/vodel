<?hh //decl
namespace Vodel\Tests\Validators;

use Vodel\Validators;

class UrlTest extends \PHPUnit_Framework_TestCase
{
  protected \Vodel\Url $property = '';

  public function testGetType()
  {
    $prop = new \ReflectionProperty($this, "property");
    $validator = new Validators\Url();
    $this->assertEquals($prop->getTypeText(), $validator->getTarget());
  }

  public function testCheck()
  {
    $validator = new Validators\Url();
    $this->assertFalse($validator->check("name@email.com"));
    $this->assertFalse($validator->check(100));
    $this->assertFalse($validator->check("name"));
    $this->assertTrue($validator->check("http://google.com"));
  }

  public function testErrorMessage()
  {
    $validator = new Validators\Url();
    $this->assertNotEmpty($validator->getErrorMessage());
  }

}
