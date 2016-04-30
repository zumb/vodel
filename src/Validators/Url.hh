<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Url extends FilterVar
{
  public function __construct() {
    parent::__construct(FILTER_VALIDATE_URL);
  }

  public function getErrorMessage():string
  {
    return "Value is not a valid URL address";
  }

}
