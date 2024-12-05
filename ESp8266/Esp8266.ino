#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
 // Wifi name
 #define WLAN_SSID "Pixel_7518"
 // Wifi password
 #define WLAN_PASS "123456789"
// setup Adafruit
 #define AIO_SERVER "io.adafruit.com"
 #define AIO_SERVERPORT 1883
 // fill your username
 #define AIO_USERNAME "hieu219"
 // fill your key
 #define AIO_KEY "aio_AUae696yn2sEH20zcEc2tJZaSeCT"

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





// if( Serial . available ()){
 //int msg = Serial . read ();
 
//  temp = Serial.parseFloat();
//  light_pub . publish(temp);
//  Serial.println(temp);
//  if(msg == 'o') Serial . print ('O');
//  else if(msg == 'a') light_pub . publish (0);
//  else if(msg == 'A') light_pub . publish (1);
// }
// }


 led_counter ++;
 if( led_counter == 100) {
 // every 1s
 led_counter = 0;
 // toggle LED
 if( led_status == HIGH ) led_status = LOW ;
 else led_status = HIGH ;

 digitalWrite (2, led_status );
 }


//delay (30000) ;
 }