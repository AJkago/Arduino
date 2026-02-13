#include <Wire.h>
#include <Zanshin_BME680.h>

//BME680 settings
#define BME_SCL 22
#define BME_SDA 21


BME680_Class BME680;
uint8_t i2c_addr = 0x77;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);

 /*BME680 settings*/
 uint8_t osrs_t = 1;
 uint8_t osrs_p = 1;
 uint8_t osrs_h = 1;
 uint8_t bme680mode = 3;
 uint8_t t_sb = 5;
 uint8_t filter = 0;
 pinMode(BME_VIN,INPUT);
 pinMode(BME_SCL,OUTPUT);
  digitalWrite(BME_SCL,HIGH);
 pinMode(BME_SDA,OUTPUT);
  digitalWrite(BME_SDA,HIGH);
 pinMode(BME_GND,OUTPUT);
  digitalWrite(BME_GND,LOW);

 Wire.begin(BME_SCL,BME_SDA);
 BME680.setMode(i2c_addr,osrs_t,osrs_p,osrs_h,bme680mode,t_sb,filter);]
 BME680.readTrim();
}

void loop() {
  // put your main code here, to run repeatedly:
 double temp_act,press_act,hum_act;

 BME680.readData(&temp_act,&press_act,&hum_act);

  Serial.print("////\nTEMP : ");
  Serial.println(temp_act);
  Serial.print(" DegC \ nPRESS : ");
  Serial.println(press_act);
  Serial.print(" hPa \ nHUM : ");
  Serial.println(hum_act);

 delay(300000);
}
