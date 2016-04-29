<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;

class Url extends FilterVar
{
  public function __construct() {
    parent::__construct(FILTER_VALIDATE_URL);
  }

  public function getFailures():Vector<string>
  {
    return Vector{"Value is not a valid URL address"};
  }

}
