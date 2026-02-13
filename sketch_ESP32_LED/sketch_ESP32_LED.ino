int portno=5;
void setup() {
  // put your setup code here, to run once:
 pinMode(portno,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(portno,HIGH);
 delay(500);
 digitalWrite(portno,LOW);
 delay(500);
 
}
