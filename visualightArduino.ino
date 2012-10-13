
// (Based on Ethernet's WebClient Example)

#include <SPI.h>
#include <WiFly.h>

#include "Credentials.h"


int _red = 255;
int _green = 255;
int _blue = 255;
int _blinkMe = 0;

//Client client(server, 80);
long previousMillis = 0;        // will store last time LED was updated
long interval = 100;           // interval at which to blink (milliseconds)
int ledState = HIGH;

WiFlyClient client;

void setup() {
  analogWrite(11, _red);
  analogWrite(10, _green);
  analogWrite(9, _blue);
  Serial.begin(9600);
  //Serial1.begin(9600);
  //delay(2000);
  delay(5000);
  WiFly.setUart(&Serial);
  WiFly.begin();
  
//  if (!WiFly.join(ssid, passphrase)) {
//    //Serial.println("Association failed.");
//    while (1) {
//      // Hang on failure.
//    }
//  }  

  //Serial.println("connecting...");
  delay(1000);
  if (client.connect("leifp.com", 5001)) {
    //Serial.println("connected");
    client.println("hello from arduino!");
    //client.println();
  } else {
    //Serial.println("connection failed");
  }
  
}

void loop() {
  if (client.available()>1) {
    //char c = client.read();
    _red = client.parseInt();
    _green = client.parseInt();
    _blue = client.parseInt();
    _blinkMe = client.parseInt();
//    _red = 255 - _red;
//    _green = 255 - _green;
//    _blue = 255 - _blue;
    analogWrite(11, _green);
    analogWrite(10, _red);
    analogWrite(9, _blue);
    
//    Serial.print(_red);
//    Serial.print("\t");
//    Serial.print(_green);
//    Serial.print("\t");
//    Serial.print(_blue);
//    Serial.println();
  }
  if(_blinkMe == 1){
      blinkLED();
    }

  
  if (!client.connected()) {
    //Serial.println();
    //Serial.println("disconnecting.");
    client.stop();
    client.connect("leifp.com", 5001);
    delay(3000);
  }
}
void blinkLED(){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    if (ledState == LOW){
      analogWrite(11, _green);
      analogWrite(10, _red);
      analogWrite(9, _blue);
      ledState = HIGH;
    }
    else{
      analogWrite(11, 0);
      analogWrite(10, 0);
      analogWrite(9, 0);
      ledState = LOW;
    }
      
  }
}


