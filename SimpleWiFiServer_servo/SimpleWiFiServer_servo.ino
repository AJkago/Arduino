#include <Servo.h>

/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32
31.01.2017 by Jan Hendrik Berlin

 */

#include <WiFi.h>

Servo servo1;

const char* ssid     = "";
const char* password = "";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    delay(100);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();

    servo1.attach(13);

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (!client) {                             // if you get a client,
    return;
    }

    Serial.println("New Client.");           // print a message out the serial port
    while (!client.available()) {            // loop while the client's connected
      delay(1);
    }
    String req = client.readStringUntil('\r');
    Serial.println(req);
    client.flush();

    int val;
    if(req.indexOf("/gpio/0") !=-1){val=0;}
    else if(req.indexOf("/gpio/30") !=-1){val=30;}
    else if(req.indexOf("/gpio/60") !=-1){val=60;}
    else if(req.indexOf("/gpio/90") !=-1){val=90;}
    else if(req.indexOf("/gpio/120") !=-1){val=120;}
    else if(req.indexOf("/gpio/150") !=-1){val=150;}
    else{
      Serial.print("REQ:");
      Serial.println(req);
      Serial.println("invalid request");
      client.stop();
      return;
    }

    servo1.write(val);

    client.flush();

    String s ="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
    s += (val)?"high":"low";
    s += "<ul>";
    s += "<li><a href='/gpio/0/'>0</a></li>\n";
    s += "<li><a href='/gpio/30/'>30</a></li>\n";
    s += "<li><a href='/gpio/60/'>60</a></li>\n";
    s += "<li><a href='/gpio/90/'>90</a></li>\n";
    s += "<li><a href='/gpio/120/'>120</a></li>\n";
    s += "<li><a href='/gpio/150/'>150</a></li>\n";
    s += "</ul>\n";
    s += "</html>\n";

    // close the connection:
    client.print(s);
    delay(10);
    Serial.println("Client Disconnected.");
  }
