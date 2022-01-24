#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SS_PIN D8
#define RST_PIN D0
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
 
const char* ssid = "your_id";
const char* password = "your_pass";


 char Url[60] ="http://{SERVER_ADDRESS}:3000/api/v1/tickets/";
 
WiFiClient client;
// Init array that will store new NUID
byte nuidPICC[4];

void sendToServer(char byteArray[5])
{
    char temp[60] ="\0" ;
    strcpy(temp,Url);
    HTTPClient http;    //Declare object of class HTTPClient
    strcat(temp,byteArray);
    Serial.print("Url = ");
    Serial.println(temp);
    
    
    http.begin(client,temp);      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.GET();   //Send the request
    String payload = http.getString();                  //Get the response payload

    if(httpCode == 200)
    {
      Serial.println("Correct card");
      
    }
    else
    {
      Serial.println("Card not detected");
    }


    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    
 
    http.end();  //Close connection
}



void setup() {
 Serial.begin(115200);
 SPI.begin(); // Init SPI bus
 rfid.PCD_Init(); // Init MFRC522
 Serial.println();
 Serial.print(F("Reader :"));
 rfid.PCD_DumpVersionToSerial();
 for (byte i = 0; i < 6; i++) {
   key.keyByte[i] = 0xFF;
 }
 Serial.println();
 Serial.println(F("This code scan the MIFARE Classic NUID."));
 Serial.print(F("Using the following key:"));
 printHex(key.keyByte, MFRC522::MF_KEY_SIZE);


   WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
}
void loop() {
  
 // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
 if ( ! rfid.PICC_IsNewCardPresent())
   return;
 // Verify if the NUID has been readed
 if ( ! rfid.PICC_ReadCardSerial())
   return;
   
 Serial.print(F("PICC type: "));
 MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
 Serial.println(rfid.PICC_GetTypeName(piccType));
 
 // Check is the PICC of Classic MIFARE type
 if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
     piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
     piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
   Serial.println(F("Your tag is not of type MIFARE Classic."));
   return;
 }

 char stringArray[5];
 int i;
 for (i=0; i<4; i++) {
    sprintf(stringArray+i*2, "%02x", rfid.uid.uidByte[i]);
}

Serial.print("Byte to String = ");
Serial.println(stringArray);
sendToServer(stringArray);
 
 if (rfid.uid.uidByte[0] != nuidPICC[0] ||
     rfid.uid.uidByte[1] != nuidPICC[1] ||
     rfid.uid.uidByte[2] != nuidPICC[2] ||
     rfid.uid.uidByte[3] != nuidPICC[3] ) {
   Serial.println(F("A new card has been detected."));
   
   // Store NUID into nuidPICC array
   for (byte i = 0; i < 4; i++) {
     nuidPICC[i] = rfid.uid.uidByte[i];
   }
   
   Serial.println(F("The NUID tag is:"));
   Serial.print(F("In hex: "));
   printHex(rfid.uid.uidByte, rfid.uid.size);
   Serial.println();
   
   Serial.print(F("In dec: "));
   printDec(rfid.uid.uidByte, rfid.uid.size);
   Serial.println();
 }
 else Serial.println(F("Card read previously."));
 // Halt PICC
 rfid.PICC_HaltA();
 // Stop encryption on PCD
 rfid.PCD_StopCrypto1();
}
/**
   Helper routine to dump a byte array as hex values to Serial.
*/
void printHex(byte *buffer, byte bufferSize) {
 for (byte i = 0; i < bufferSize; i++) {
   Serial.print(buffer[i] < 0x10 ? " 0" : " ");
   Serial.print(buffer[i], HEX);
 }
}
/**
   Helper routine to dump a byte array as dec values to Serial.
*/
void printDec(byte *buffer, byte bufferSize) {
 for (byte i = 0; i < bufferSize; i++) {
   Serial.print(buffer[i] < 0x10 ? " 0" : " ");
   Serial.print(buffer[i], DEC);
 }
}
