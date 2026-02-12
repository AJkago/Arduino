#define DATA 2
#define LATCH 3
#define CLOCK 4

//  0b10000000   DP
//  0b01000000   D
//  0b00100000   E
//  0b00010000   F
//  0b00001000   A
//  0b00000100   G
//  0b00000010   C
//  0b00000001   B

static const int num[] {
  0b01111011,   //ZERO
  0b00000011,   //ONE
  0b01101101,   //TWO
  0b01001111,   //THREE
  0b00010111,   //FOUR
  0b01011110,   //FIVE
  0b01110110,   //SIX
  0b00001011,   //SEVEN
  0b01111111,   //EIGHT
  0b01011111,   //NINE
};

int count;

void setup()
{
  count = 0;
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop()
{
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, 8, num[count]);
  digitalWrite(LATCH, HIGH);
  delay(1000);
  if (count == 9)
    count = 0;
  else
    count++;
}
