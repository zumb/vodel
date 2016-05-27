<?hh //strict
namespace Zumb\Vodel\Validators;

use Zumb\Vodel\Interfaces\Validator;
use Zumb\Vodel\Interfaces\TransformsData;

class DateTime implements Validator, TransformsData<string, \DateTime>
{
  public static string $FORMAT = \DateTime::ISO8601;

  public function validate(mixed $value):bool
  {
    if(is_string($value)) {
      return $this->transform($value) instanceof \DateTime;
    }
    return false;
  }

  public function transform(string $value):?\DateTime
  {
    return \DateTime::createFromFormat(self::$FORMAT, $value) ?: null;
  }

  public function getErrorMessage():string
  {
    return "Should be a valid date, using format ".self::$FORMAT;
  }
}
