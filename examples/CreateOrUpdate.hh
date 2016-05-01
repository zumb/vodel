<?hh //partial
namespace ExampleCreateUpdate;
/* In this example we will show how you can use constructor parameters
to set different validations for create or update a model */

require_once 'vendor/autoload.php';

class ProductModel implements \Vodel\Interfaces\JsonModel
{
  /* This property is public, so it will be validated and loaded, but
    since is not in the constructor, it's not required when creating an object
    but it is when updating */
  public string $description = '';

  public Vector<string> $versions = Vector{};

  public Vector<CommentsModel> $comments = Vector{};

  public function __construct(
    /* This property is required on create, but it can't be changed on update */
    protected string $type,
    /* This property is required on create, and it will be required on update */
    public string $name,
    /* This property is required on create, and it's not required on update */
    public ?float $value
  ) {}
}

class CommentsModel implements \Vodel\Interfaces\JsonModel
{
  public function __construct(
    protected string $name,
    protected string $text
  ) {
    $this->setText($text);
  }

  public function setText($text):void
  {
    $this->text = strip_tags($text);
  }
}

/* And now just receive the data, and get it validated
 */
function main ():void {
  // Create the validation repository
  $validations = new \Vodel\ValidationRepository(new \Vodel\ClassUtil(), new \Vodel\Reflection\TypeInspector());
  // Create adapter without object, so it will create one and use constructor validations
  $adapter = new \Vodel\Adapters\ModelAdapter($validations, new \ReflectionClass(ProductModel::class));
  // We will take the input from a file, it should come from the request
  if($adapter->validate(json_decode(file_get_contents(__DIR__."/json/productCreate.json")))) {
    echo "The input is valid";
    var_dump($adapter->transform(null));
  } else {
    var_dump(json_encode($adapter->getFailures()));
  }

  // Create adapter with an object, so it will create one and use constructor validations
  $productFromDB = new ProductModel("Electronics", "Computer", 1500.50);
  $adapter = new \Vodel\Adapters\ModelAdapter($validations, new \ReflectionClass($productFromDB), $productFromDB);
  // We will take the input from a file, it should come from the request
  if($adapter->validate(json_decode(file_get_contents(__DIR__."/json/productUpdate.json")))) {
    echo "The input is valid";
    var_dump($adapter->transform(null));
  } else {
    var_dump(json_encode($adapter->getFailures()));
  }
}

main();
