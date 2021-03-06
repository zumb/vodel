<?hh //strict
namespace Zumb\Vodel\Validators;

use Zumb\Vodel\Interfaces\Validator;

class Email extends FilterVar
{
  public function __construct() {
    parent::__construct(FILTER_VALIDATE_EMAIL);
  }

  public function getErrorMessage():string
  {
    return "Should be a valid email address";
  }
}
