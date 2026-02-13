#include <WiFi.h>
#include <Ambient.h>

#define TIME_TO_SLEEP 60

WiFiClient client;
Ambient ambient;

const char* ssid = "";
const char* password = "";

unsigned int channelId = ;
const char* writeKye = "";

#define SMELLPIN 35

void setup() {
  // put your setup code here, to run once:
  unsigned long starttime=millis();
  Serial.begin(115200);
  while(!Serial);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi connected\r\nIP address: ");
  Serial.println(WiFi.localIP());

  ambient.begin(channelId,writeKye,&client);

  pinMode(SMELLPIN,INPUT);

  float smellvolume[10];
  smellvolume[0] = analogRead(SMELLPIN);
  float a = smellvolume[0]/0.3706;
  float R0 = 56.2;
  Serial.print("Freshair: ");
  Serial.println(smellvolume[0]);
  Serial.println("Please breath in 10 second.");
  delay(1000);

  int i;
  float maxvolume;
  for(i=1;i<10;i++){
    smellvolume[i] = analogRead(SMELLPIN);
    if(smellvolume[i]>smellvolume[i-1]){
      maxvolume = smellvolume[i];
    }
    delay(1000);
  }
  Serial.print("Smellair: ");
  Serial.println(maxvolume);
  float answer = maxvolume / a;

  float RsR0 = ((1.03 - answer) / answer * 100) / R0;
  Serial.print("Rs/R0: ");
  Serial.println(RsR0);

  ambient.set(1, RsR0);
  ambient.send();

  uint64_t sleeptime = TIME_TO_SLEEP *1000000 -(millis()-starttime)*1000;
  esp_deep_sleep(sleeptime);
}

void loop() {
  // put your main code here, to run repeatedly:

}
