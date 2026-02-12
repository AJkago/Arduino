int IN1 = 5;
int IN2 = 6;

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  delay(1000);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  delay(1000);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  delay(1000);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,HIGH);
  delay(1000);
  
}
