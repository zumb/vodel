<?hh //strict
namespace Vodel\Validators;

use Vodel\Interfaces\Validator;
use Vodel\Interfaces\TransformsData;

class DateTime implements Validator, TransformsData<\DateTime>
{
  protected string $format = \DateTime::ISO8601;

  public function getTarget():string
  {
    return 'DateTime';
  }

  public function check(mixed $value):bool
  {
    return $this->transform($value) instanceof \DateTime;
  }

  public function getErrorMessage():string
  {
    return "Property is not a valid date time (expected format {$this->format})";
  }

  public function transform(mixed $value):?\DateTime
  {
    $date = \DateTime::createFromFormat($this->format, $value);
    if($date instanceof \DateTime) {
      return $date;
    }
    return null;
  }
}
