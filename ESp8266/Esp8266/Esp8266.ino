#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
 // Wifi name
 #define WLAN_SSID "..."
 // Wifi password
 #define WLAN_PASS "..."
// setup Adafruit
 #define AIO_SERVER "io.adafruit.com"
 #define AIO_SERVERPORT 1883
 // fill your username
 #define AIO_USERNAME "..."
 // fill your key
 #define AIO_KEY "..."

 // setup MQTT
WiFiClient client ;
Adafruit_MQTT_Client mqtt (& client , AIO_SERVER ,
AIO_SERVERPORT , AIO_USERNAME , AIO_KEY );

 // set publish
Adafruit_MQTT_Publish light_pub = Adafruit_MQTT_Publish (&
mqtt , AIO_USERNAME "/feeds/temp");
 int led_counter = 0;
 int led_status = HIGH ;
int x = 0;
float temp;
 void setup () {
 // put your setup code here , to run once :
 // set pin 2,5 as OUTPUT
 pinMode (2, OUTPUT );
 pinMode (5, OUTPUT );
 // set busy pin HIGH
 digitalWrite (5, HIGH );

 Serial . begin (115200) ;

 // connect Wifi
 WiFi . begin ( WLAN_SSID , WLAN_PASS );
 while ( WiFi . status () != WL_CONNECTED ) {
 delay (500) ;
 }
// Serial.println("Wi-fi is OK!!");
 while (mqtt.connect() != 0) {
 delay (500) ;
  }
 // finish setup , set busy pin LOW
 digitalWrite (5, LOW);
}
 void loop () {
 // put your main code here , to run repeatedly :

if (Serial.available() > 0) {
    String str = Serial.readString();
    str.trim();
    light_pub . publish(str.toFloat());
  }
}
