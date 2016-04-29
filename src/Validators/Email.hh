<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Email extends FilterVar
{
  public function __construct() {
    parent::__construct(FILTER_VALIDATE_EMAIL);
  }

  public function getFailures():Vector<string>
  {
    return Vector{"Invalid email"};
  }
}
