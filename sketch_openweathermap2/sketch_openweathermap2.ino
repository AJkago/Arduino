#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* password =  "";

const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=kagoshima,jp&APPID=";
const String key = "";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

}

void loop() {

  if ((WiFi.status() == WL_CONNECTED)) {

    HTTPClient http;

    http.begin(endpoint + key); //URLを指定
    int httpCode = http.GET();  //GETリクエストを送信

    if (httpCode > 0) { //返答がある場合

        String payload = http.getString();  //返答（JSON形式）を取得
        Serial.println(httpCode);
        Serial.println(payload);

        //jsonオブジェクトの作成
        DynamicJsonBuffer jsonBuffer;
        String json = payload;
        JsonObject& weatherdata = jsonBuffer.parseObject(json);

        //パースが成功したかどうかを確認
        if(!weatherdata.success()){
          Serial.println("parseObject() failed");
        }

        //各データを抜き出し
        const char* weather = weatherdata["weather"][0]["main"].as<char*>();
        const double temp = weatherdata["main"]["temp"].as<double>();
        const double feels_like = weatherdata["main"]["feels_like"].as<double>();
        const double windspeed = weatherdata["wind"]["speed"].as<double>();
        const double humidity = weatherdata["main"]["humidity"].as<double>();
        Serial.print("天気:");
        Serial.println(weather);
        Serial.print("現在の気温:");
        Serial.println(temp-273.15);
        Serial.print("体感気温:");
        Serial.println(feels_like-273.15);
        Serial.print("風速:");
        Serial.println(windspeed);
        Serial.print("湿度:");
        Serial.println(humidity);
      }
    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }

  delay(300000);   //300秒おきに更新

}
