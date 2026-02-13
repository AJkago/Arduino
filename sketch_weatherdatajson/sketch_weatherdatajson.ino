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
        Serial.print("weather:");
        Serial.println(weather);
        Serial.print("temperature:");
        Serial.println(temp-273.15);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //リソースを解放
  }
 
  delay(3600000);   //3600秒(60分)おきに更新
 
}
