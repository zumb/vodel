<?hh //strict
namespace MyProject;

use Vodel\Interfaces\JsonModel;
use Vodel\Validators;

/* Vodel relies on type hints for matching validation rules,
 * you can define custom types to apply custom validation rules
 */
type Color = string;

/* You can also simply define an enum, for a simple value must match
 * validation */
enum Role: string {
  USER = "user";
  EDITOR = "editor";
  ADMIN = "admin";
}

/* Implement JsonModel */
class UserModel implements JsonModel
{
  /* Vodel also includes some common types you can use, like Email */
  public \Vodel\Email $email = '';

  /* Or Url */
  public \Vodel\Url $website = '';

  /* String also will be validated, number only will fail */
  public string $name = '';

  /* Attributes will be required unless you make them nullables */
  public ?string $lastName;

  /* Using an enum to validate values */
  public Role $role = Role::USER;

  /* Use your custom type, also in arrays (you could have used also an enum) */
  public array<Color> $favoriteColors = [];

  /* Relate another JsonModel object as property or array, it will
  * get validated and the whole validation will fail if there is any
  * validation error
  */
  public array<Phone> $phones = [];

  /* Protected properties don't count */
  protected ?string $description;

  /* Unless you write a setter method for them */
  public function setDescription(string $value):void
  {
    $this->description = strip_tags($value);
  }

}

/* Another model structure to save data */
class Phone implements JsonModel
{
  public string $type = '';

  public string $number = '';
}

/* Custom Validator for our previously defined Role type */
class ColorValidator extends Validators\InArray<string>
{
  protected array<string> $values = ["orange", "blue", "green"];
}

/* And now just receive the data, get it validated, and fill
 * your objects
 */
function main ():void {
  /* Create the adapter and add any custom validation */
  $adapter = new \Vodel\JsonModelAdapter(new UserModel());
  $adapter->addValidator("MyProject\Role", new ColorValidator());
  $jsonInput = json_decode("{}");
  /* Take your JSON and send it for validation */
  if($adapter->validate($jsonInput)) {
    /* Fill your model */
    $adapter->fillWith($jsonInput);
  }
}
