#include <LiquidCrystal.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  float temperature = sensorValue*(5.0/1023.0)*100-273;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(String(temperature)+'C');

  delay(1000);
}
