#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
AltSoftSerial gpsSerial;
#include <String.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3); 
// Create a TinyGPS++ object
TinyGPSPlus gps;

char incomingByte; 
String incomingData;
bool atCommand = true;
 
int relay = 13;
int led = 12;
int index = 0;
String number = "";
String message = "";

int D0, D1, D2, D3;
//int Data;

#define D0pin 11
#define D1pin 4
#define D2pin 5
#define D3pin 6


void ReadDataIsr() {
  
  D0 = digitalRead(D0pin);
  D1 = digitalRead(D1pin);
  D2 = digitalRead(D2pin);
  D3 = digitalRead(D3pin);

  Serial.println( (String)D0 + ", " +  
                  (String)D1 + ", " + 
                  (String)D2 + ", " + 
                  (String)D3 );  
}

void displayInfo()
{
  delay(1000);
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  delay(50);
}


void receivedMessage(String inputString){
   
  //Get The number of the sender
  index = inputString.indexOf('"')+1;
  inputString = inputString.substring(index);
  index = inputString.indexOf('"');
  number = inputString.substring(0,index);
  Serial.println("Number: " + number);
 
  //Get The Message of the sender
  index = inputString.indexOf("\n")+1;
  message = inputString.substring(index);
  message.trim();
  Serial.println("Message: " + message);
        
  message.toUpperCase(); // uppercase the message received


   if (number.indexOf("9379103720") > -1){ 
  if (message.indexOf("GPS") > -1){
  mySerial.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(50);  
  mySerial.println("AT+CMGS=\"+989379103720\""); // Replace it with your mobile number
  delay(50);
  mySerial.print("https://google.com/maps?q=");   // The SMS text you want to send
  delay(50);
  mySerial.print(gps.location.lat(), 6);   // The SMS text you want to send
  delay(50);
  mySerial.print(',');   // The SMS text you want to send
  delay(50);
  mySerial.println(gps.location.lng(), 6);   // The SMS text you want to send
  delay(50);
  mySerial.println((char)26);  // ASCII code of CTRL+Z
  delay(50);
  mySerial.println();
  delay(50);

        
   }} 

   
 
  //turn Led ON or OFF
 if (number.indexOf("9379103720") > -1){
  if (message.indexOf("LED_ON") > -1){
      digitalWrite(led, HIGH);
      Serial.println("Command: Led Turn On.");

  mySerial.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(50);  
  mySerial.println("AT+CMGS=\"+989379103720\""); // Replace it with your mobile number
  delay(50);
  mySerial.println("Led Turn On.");   // The SMS text you want to send
  delay(50);
  mySerial.println((char)26);  // ASCII code of CTRL+Z
  delay(50);
  mySerial.println();
  delay(50);
      



      
   }  }     

      if (number.indexOf("9379103720") > -1){
  if (message.indexOf("LED_OFF") > -1){
      digitalWrite(led, LOW);
      Serial.println("Command: Led Turn Off.");

  mySerial.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(50);  
  mySerial.println("AT+CMGS=\"+989379103720\""); // Replace it with your mobile number
  delay(50);
  mySerial.println("Led Turn Off.");   // The SMS text you want to send
  delay(50);
  mySerial.println((char)26);  // ASCII code of CTRL+Z
  delay(50);
  mySerial.println();
  delay(50);
      



      
   }  } 
     //turn relay ON or OFF
if (number.indexOf("9379103720") > -1){
  if (message.indexOf("RELAY_ON") > -1){
      digitalWrite(relay,LOW);
      Serial.println("Command: Relay Turn On.");

  mySerial.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(50);  
  mySerial.println("AT+CMGS=\"+989379103720\""); // Replace it with your mobile number
  delay(50);
  mySerial.println("Relay Turn On.");   // The SMS text you want to send
  delay(50);
  mySerial.println((char)26);  // ASCII code of CTRL+Z
  delay(50);
  mySerial.println();
  delay(50);
      



      
   }  } 
         if (number.indexOf("9379103720") > -1){
  if (message.indexOf("RELAY_OFF") > -1){
      digitalWrite(relay,HIGH);
      Serial.println("Command: Relay Turn Off.");

  mySerial.println("AT+CMGF=1");    //Set the GSM Module in Text Mode
  delay(50);  
  mySerial.println("AT+CMGS=\"+989379103720\""); // Replace it with your mobile number
  delay(50);
  mySerial.println("Relay Turn Off.");   // The SMS text you want to send
  delay(50);
  mySerial.println((char)26);  // ASCII code of CTRL+Z
  delay(50);
  mySerial.println();
  delay(50);
      



      
   }  } 
   delay(50);     

  }

void setup(){
  attachInterrupt(digitalPinToInterrupt(10), ReadDataIsr, RISING);
  pinMode(INPUT, D0pin);
  pinMode(INPUT, D1pin);
  pinMode(INPUT, D2pin);
  pinMode(INPUT, D3pin);
  digitalWrite(relay,HIGH);
    Serial.begin(9600);
    mySerial.begin(9600);
    gpsSerial.begin(9600);
    pinMode(relay, OUTPUT); 
    pinMode(led, OUTPUT);     
    // Check if you're currently connected to SIM800C 
    while(!mySerial.available()){
      mySerial.println("AT");
      delay(50); 
      Serial.println("connecting....");
    }
    Serial.println("Connected..");  
    mySerial.println("AT+CMGF=1");  //Set SMS Text Mode 
    delay(50);  
    mySerial.println("AT+CNMI=1,2,0,0,0");  //procedure, how to receive messages from the network
    delay(50);
    mySerial.println("AT+CMGL=\"REC UNREAD\""); // Read unread messages
    Serial.println("Ready to receive Commands..");  
 }
 
void loop(){
  if(mySerial.available()){
      delay(50);
      // Serial buffer
      while(mySerial.available()){
        incomingByte = mySerial.read();
        incomingData += incomingByte;
       }
        delay(10); 
        if(atCommand == false){
          receivedMessage(incomingData);
        }
        else{
          atCommand = false;
        }        
        //delete messages to save memory
        if (incomingData.indexOf("OK") == -1){
          mySerial.println("AT+CMGDA=\"DEL ALL\"");
          delay(50);
          atCommand = true;
        }        
        incomingData = "";
  }


  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }

  
}
 

