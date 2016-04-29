<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;
use Vodel\Interfaces\TransformsData;

class DateTime implements Validator, TransformsData<string, \DateTime>
{
  public static string $FORMAT = \DateTime::ISO8601;

  public function validate(mixed $value):bool
  {
    return $value instanceof \DateTime;
  }

  public function transform(string $value):?\DateTime
  {
    return \DateTime::createFromFormat(self::$FORMAT, $value) ?: null;
  }

  public function getFailures():Vector<string>
  {
    return Vector{"Invalid date"};
  }
}
