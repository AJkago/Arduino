//www.elegoo.com
//2016.12.9

int latchPin = 11;
int clockPin = 9;
int dataPin = 12;

int leds = 0;

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void setup()
{
pinMode(latchPin, OUTPUT);
pinMode(dataPin, OUTPUT);
pinMode(clockPin, OUTPUT);
updateShiftRegister();
Serial.begin(9600);
while (! Serial); // Wait until Serial is ready - Leonardo
Serial.println("Enter LED Number 0 to 7 or 'x' to clear");
}

/*   The most common method of using 74CH595
 *   lctchPin->LOW : Begin transmitting signals.
 *   shiftOut(dataPin, clockPin, bitOrder, value)
 *   dataPin: the pin on which to output each bit. Allowed data types: int.
 *   clockPin: the pin to toggle once the dataPin has been set to the correct value. Allowed data types: int.
 *   bitOrder: which order to shift out the bits; either MSBFIRST or LSBFIRST. (Most Significant Bit First, or, Least Significant Bit First).
 *   value: the data to shift out. Allowed data types: byte. 
 *   lctchPin->HIch : The end of the transmission signal.
*/

void loop()
{
if (Serial.available())
 {
 char ch = Serial.read();
 if (ch >= '0' && ch <= '7')
  {
  int led = ch - '0'; bitSet(leds, led);
  updateShiftRegister();
  Serial.print("Turned on LED ");
  Serial.println(led);
  }
 if (ch == 'x')
 {
 leds = 0; updateShiftRegister();
 Serial.println("Cleared");
 }
 }
}
