<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Url extends FilterVar
{
  public static int $FLAG = FILTER_VALIDATE_URL;

  public function getTarget():string
  {
    return 'Vodel\Url';
  }

  public function getErrorMessage():string
  {
    return "Value is not a valid URL address";
  }

}
