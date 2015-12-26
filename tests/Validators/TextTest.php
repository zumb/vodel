<?hh //decl
namespace Vodel\Tests\Validators;

use Vodel\Validators;

class TextTest extends \PHPUnit_Framework_TestCase
{

  protected string $property = '';

  public function testGetType()
  {
    $prop = new \ReflectionProperty($this, "property");
    $validator = new Validators\Text();
    $this->assertEquals($prop->getTypeText(), $validator->getTarget());
  }

  public function testCheck()
  {
    $validator = new Validators\Text();
    $this->assertTrue($validator->check("text"));
    $this->assertFalse($validator->check(100));
  }

  public function testErrorMessage()
  {
    $validator = new Validators\Text();
    $this->assertNotEmpty($validator->getErrorMessage());
  }

}
