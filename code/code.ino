#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_MQTT_FONA.h>
#include<ESP8266WiFi.h>
#include"Adafruit_MQTT_Client.h"
int sensor_pin = A0;
#define wifi "IoT"
#define password "12345678"
#define server "io.Adafruit.com"
#define led 16
int pump = 2;
#define port 1883
#define username "vikramadityasinghs"
#define key "aio_vJEu96fjstprQRVuqwALfCB3gdtS"
WiFiClient esp;
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Publish temp=Adafruit_MQTT_Publish(&mqtt,username"/feeds/moisture-of-soil");
int output_value ;

void setup() {

   Serial.begin(9600);
   pinMode(pump,OUTPUT);
    digitalWrite(pump, HIGH);

   Serial.println("sensor reading...");
Serial.println("Adafruit MQTT demo");
Serial.println("Connecting to");
Serial.println(wifi);
WiFi.begin(wifi,password);
while(WiFi.status()!=WL_CONNECTED)
{delay(500);
Serial.println(".");
}
Serial.println("wifi connected");
Serial.println("ip adress");
Serial.println(WiFi.localIP());
Serial.println("connecting to mqtt");

while(mqtt.connect())
{Serial.println(".");}

   delay(2000);

   }

void loop() {
 float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");
  if(moisture_percentage>60)
  {
    Serial.println("OVERWATERED");
    
    }
else if(moisture_percentage>40)
{
   Serial.println("WATERED correctly");
  }
else if(moisture_percentage>10)
{
   Serial.println("UNDERWATERED");
   digitalWrite(pump,LOW);
   delay(2000);
   digitalWrite(pump,HIGH);
  }
  delay(1000);  
  temp.publish(moisture_percentage);
  delay (5000);
   }
