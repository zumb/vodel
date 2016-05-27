<?hh //partial
namespace MyProject;

require_once 'vendor/autoload.php';

use Zumb\Vodel\Interfaces\JsonModel;
use Zumb\Vodel\Validators;

/* Vodel relies on type hints for matching validation rules,
 * you can define custom types to apply custom validation rules
 */
type Color = string;
type Email = string;
type Url = string;

/* You can also simply define an enum, for a simple value must match
 * validation */
enum Role: string {
  USER = "user";
  EDITOR = "editor";
  ADMIN = "admin";
}

/* Implement JsonModel on your model definitions */
class UserModel implements JsonModel
{
  /* Here we set the properties in the constructor, so they will need to
   be defined on create (check the CreateOrUpdate example) */
  public function __construct(
    /* Vodel includes some common types you can use, like Email */
    public Email $email,

    /* Or Url */
    public Url $website,

    /* Here we use our custom type Color, that is a string, but inside an array
    that means that the user can send an array of values, and each of them
    will have to pass the validation associated with the Color type */
    public Vector<Color> $favoriteColors,

    /* A simple validation will check for the scalar type */
    public string $name,

    /* Here we use our enum type, the user will have to send a valid value */
    public Role $role,

    /* Vodel includes validation for DateTimes, you can basically associate
    any class with a custom validator and data transformer  */
    public \DateTime $birthDate,

    /* Relate another JsonModel object as property or vector, it will
    * get validated and the whole validation will fail if there is any
    * validation error
    */
    public Vector<PhoneModel> $phones,

    /* To define an optional value, just assign a value to it */
    public ?string $lastName = null
  ) {}

  /* Protected properties don't count */
  protected ?string $description;

  /* Unless you write a setter method for them */
  public function setDescription(string $value):void
  {
    $this->description = strip_tags($value);
  }

}

/* This is our PhoneModel that we used previously */
class PhoneModel implements JsonModel
{
  public function __construct(
    public string $type,

  // Check for a numeric input
    public int $number
  ) {}
}

/* Custom Validator for our previously defined Color type
 * in this case extends InArray validator, but you can make
 * your own complex logic implementing the Validator interface
*/
class ColorValidator extends Validators\InArray<string>
{
  public function __construct() {
    parent::__construct(["orange", "blue", "green"]);
  }
}

/* And now just receive the data, and get it validated
 */
function main ():void {
  // Create the validation repository
  $validations = new \Zumb\Vodel\ValidationRepository(new \Zumb\Vodel\ClassUtil(), new \Zumb\Vodel\Reflection\TypeInspector());
  // Add custom validations
  $validations->addValidator('MyProject\Color', new ColorValidator());
  $adapter = new \Zumb\Vodel\Adapters\ModelAdapter($validations, new \ReflectionClass(UserModel::class));
  // We will take the input from a file, it should come from the request
  if($adapter->validate(json_decode(file_get_contents(__DIR__."/json/validations.json")))) {
    echo "The input is valid";
    var_dump($adapter->transform(null));
  } else {
    var_dump(json_encode($adapter->getFailures()));
  }
}

main();
