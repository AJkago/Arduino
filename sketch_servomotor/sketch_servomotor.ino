#include<Servo.h>
Servo myServo;

void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  int angle = map(sensorValue,0,1023,0,180);
  myServo.write(angle);

  delay(100);
}
