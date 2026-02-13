#include <driver/adc.h>
#include<WiFi.h>

#define TIME_TO_SLEEP 60

const char* ssid = "";
const char* password = "";
/*
const char* ssid = "Buffalo-G-C7E0";
const char* password = "6ewadx58e6utc";
*/

const char* host="";
const char* keycode= "";

float sensorTemp,sensorVoltage;
float limitTemp = 30;
bool checkTemp;
RTC_DATA_ATTR bool prevTemp=false;

const int sensorPin=32;

void beginWifi(){
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
//    Serial.print(".");
  }
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
}

void sendRequest(String _action){
//  Serial.println(_action);

//  Serial.print("connected to ");
//  Serial.println(host);

  WiFiClient client;
  const int httpPort=80;
  if(!client.connect(host,httpPort)){
//    Serial.println("connection failed");
    return;
  }

 String url = "/trigger/";
  url+= _action;
  url+= "/with/key/";
  url+= keycode;

//  Serial.print("Requesting URL: ");
//  Serial.println(url);

  client.print(String("GET ")+ url + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" +
              "Connection: close\r\n\r\n");
  unsigned long timeout =millis();
  while(client.available()==0){
    if(millis()-timeout>5000){
//      Serial.println(">>>Client Timeout !");
      client.stop();
      return;
    }
  }

  while(client.available()){
    String line=client.readStringUntil('\r');
//    Serial.print(line);
  }

//  Serial.println();
//  Serial.println("closing connection");
}

void setup() {
  // put your setup code here, to run once:
  unsigned long starttime=millis();
 adc1_config_width(ADC_WIDTH_BIT_12);
 adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);
// Serial.begin(115200);
 pinMode(sensorPin,INPUT);

 beginWifi();

 delay(1000);

/*

  // put your main code here, to run repeatedly:
*/
 int sensorValue = adc1_get_raw(ADC1_CHANNEL_4);
// Serial.print(sensorValue);
// Serial.print("  ");
 sensorVoltage = sensorValue * (25 / 4095.0);
// Serial.print(sensorVoltage);
// Serial.print("  ");
 sensorTemp = sensorVoltage * (-100) + 910;
// Serial.println(sensorTemp);

if(sensorTemp>=limitTemp)
      checkTemp= true;
     else
      checkTemp= false;

bool isTemp=checkTemp;
 if(isTemp && !prevTemp){
  sendRequest("START_Engine");
 }else if (!isTemp && prevTemp){
  sendRequest("FINISH_Engine");
 }
 prevTemp = isTemp;

// delay(15000);
//Deep sleepする時間を計算する
uint64_t sleeptime =TIME_TO_SLEEP * 1000000 - (millis() -starttime) * 1000;
esp_deep_sleep(sleeptime);
}

void loop() {
}
