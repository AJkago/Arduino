const int sensorPin = 2;

boolean previousState = LOW;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  boolean currentState = digitalRead(sensorPin);

  if((currentState == LOW)&& (previousState == HIGH)){
    count += 1;
    Serial.println(count);
    delay(10)
  }

  previousState = currentState;
  delay(100);
}
