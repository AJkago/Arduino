#include <driver/adc.h>
#include <WiFi.h>

 const char* ssid = "";
 const char* password =  "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = adc1_get_raw(ADC1_CHANNEL_0);
  Serial.println(sensorValue);

}
