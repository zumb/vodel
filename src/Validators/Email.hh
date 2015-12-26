<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Email extends RegExp
{
  public static string $PATTERN = "/^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}$/i";

  public function getTarget():string
  {
    return 'Vodel\Email';
  }

  public function getErrorMessage():string
  {
    return "Value is not an email";
  }

}
