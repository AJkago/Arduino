#include <Wire.h>
#include "Ambient.h"
#include <list>
#include <driver/adc.h>

//#define DEBUG 0

WiFiClient client;
Ambient ambient;

const char* ssid = "";
const char* password = "";

unsigned int channelId = 27187;
const char* writeKye = "9b73fa1c498ed668";

//Wi-Fi setup
void WiFi_setup(void){
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.print("WiFi connected\r\nIP address: ");
  Serial.println(WiFi.localIP());
}

/*Dust sensor variable*/
#define LED_PIN 2
#define DUST_PIN ADC1_CHANNEL_0
#define SAMPLINGTIME 280
#define DELTATIME 40
#define SLEEPTIME 9680
#define DUST_HISTORY_MAX 5


std::list<float> dustDensityHistory;
float dust = 0;

//Dust sensor setup
void GP2Y1010_setup(){
  pinMode(LED_PIN,OUTPUT);
}

//Dust sensor loop
void GP2Y1010_loop(){
digitalWrite(LED_PIN,LOW);
delayMicroseconds(SAMPLINGTIME);

int analogvalue =adc1_get_raw(ADC1_CHANNEL_0);
delayMicroseconds(DELTATIME);

digitalWrite(LED_PIN,HIGH);
delayMicroseconds(SLEEPTIME);

//dust density
float nowdust = (0.17*(analogvalue*(5.0/1024.0))-0.1)*1000;

Serial.println("---------------------");
Serial.print("analog: "); Serial.println(analogvalue);
Serial.print("dust: "); Serial.print(nowdust); Serial.println(" ug/m3");

//average
dustDensityHistory.push_front(nowdust);
while(dustDensityHistory.size()>DUST_HISTORY_MAX){
  dustDensityHistory.pop_back();
}

float avg =0;
for (auto itr = dustDensityHistory.begin(); itr!=dustDensityHistory.end(); ++itr){
  avg+=*itr;
}
dust =avg/dustDensityHistory.size();

Serial.print("dust avg: "); Serial.print(dust); Serial.println( "ug/m3");

}

/*MAIN*/

void setup() {
 Serial.begin(9600);
 WiFi_setup();
 adc1_config_width(ADC_WIDTH_BIT_12);
 adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11);
 GP2Y1010_setup();
 ambient.begin(channelId,writeKye,&client);
 Serial.println("");
}

#define DATA_SEND_CYCLE ((60*1000)*1)//1分ごとにデータ送信
long datasend_time=millis();

void loop() {
 if((millis()-datasend_time)>DATA_SEND_CYCLE){

  //get dust sensor value
  GP2Y1010_loop();
  //send data to Ambient
  ambient.set(1, dust);
  ambient.send();

  datasend_time=millis();
 }
}
