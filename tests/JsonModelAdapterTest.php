<?hh //decl
namespace Vodel\Tests;

use Vodel\Interfaces\JsonModel;
use Vodel\JsonModelAdapter;

class Model implements JsonModel
{
  public string $name;
}

class ModelNested implements JsonModel
{
  public Model $child;
}

class JsonModelAdapterTest extends \PHPUnit_Framework_TestCase
{

  public function testValidate()
  {
    $adapter = new JsonModelAdapter(new Model());
    $adapter->validate(json_decode('{"name": "test"}'));
    $this->assertCount(0, $adapter->getErrors());
    $adapter->validate(json_decode('{"lastname": "test"}'));
    $this->assertCount(1, $adapter->getErrors());
    $adapter->validate(json_decode('{"name": 10}'));
    $this->assertCount(1, $adapter->getErrors());
  }

  public function testValidateNested()
  {
    $adapter = new JsonModelAdapter(new ModelNested());
    $adapter->validate(json_decode('{"child": {"name": "test"}}'));
    $this->assertCount(0, $adapter->getErrors(), json_encode($adapter->getErrors()));
    $adapter->validate(json_decode('{"child": "test"}'));
    $this->assertCount(1, $adapter->getErrors());
  }

}
