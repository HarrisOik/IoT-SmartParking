#include <RH_NRF24.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG
#define echoPin D7 // Echo Pin
#define trigPin D6 // Trigger Pin
const String sensorId = "sensor_id";

float duration, distance;
bool spotFlag = false;

 
const char* ssid = "your_id";
const char* password = "your_pass";


 
WiFiClient client;
int gatewayID = EEPROM.read(0);

//The json object for the nodes values
const size_t CAPACITY = JSON_ARRAY_SIZE(200);
StaticJsonDocument<CAPACITY> doc;
 

 
RH_NRF24 nrf24(4, 2);

void initSensor()
{
    HTTPClient http;    //Declare object of class HTTPClient
    JsonObject object = doc.to<JsonObject>();
    String JsonMessage;

    //Initialize the json doc with the following values
    object["name"] = sensorId;
    object["status"] = false;
    serializeJson(object,JsonMessage);

    
    #ifdef DEBUG  
    serializeJson(object, Serial);
    Serial.println();
    #endif
    
    
    http.begin(client,"http://192.168.1.13:3000/api/v1/spots");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.POST(JsonMessage);   //Send the request
    String payload = http.getString();                  //Get the response payload

    #ifdef DEBUG  
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    #endif
 
    http.end();  //Close connection
}


void sendToServer(String status)
{
    HTTPClient http;    //Declare object of class HTTPClient
    JsonObject object = doc.to<JsonObject>();
    String JsonMessage;

   
    object["name"] = sensorId;
   
   
    object["status"] = status;


    
    
    

    
    serializeJson(object, Serial);
    serializeJson(object,JsonMessage);
    Serial.println();
    
    http.begin(client,"http://192.168.1.13:3000/api/v1/spots/A4");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.PATCH(JsonMessage);   //Send the request
    String payload = http.getString();                  //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
}

 
void setup()
{
  Serial.begin(115200);

  #ifdef DEBUG
  Serial.print("Receiver Started, ID: ");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print(gatewayID);
  Serial.println();
  #endif
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  initSensor();
  

}
 
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  

  duration = pulseIn(echoPin, HIGH);
  distance = duration/29/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance < 30 && spotFlag == false)
  {
    Serial.println("Car detected");
    spotFlag = true;
    sendToServer("true");
  }
  else if(distance > 30 && spotFlag == true)
  {
    Serial.println("Car left");
    spotFlag = false;
    sendToServer("false");
  }
  delay(1000);


}
