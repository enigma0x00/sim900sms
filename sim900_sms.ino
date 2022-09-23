#include <SoftwareSerial.h>
/****************************************************************************
 * written by enigma0x00
 * email:- abhishek@enigma0x00.com
 * alt:-  enigma0x00@yahoo.com
 * github:- github.com/enigma0x00
 * 
 * A Sample program to turn on/off a pin(relay) to contorl electronic devices.
 * You can add as many variablles required.
 * 
 * **************************************************************************/ 
// Configure software serial port
SoftwareSerial SIM900(8, 9); //(Rx,Tx)
 
// Variable to store text message
String textMessage;
 
// Create a variable to store Lamp state
String lampState = "HIGH";
 
// Relay connected to pin 13
const int relay = 13;
 
void setup() {
  // Automatically turn on the shield
 // digitalWrite(9, HIGH);
//  delay(1000);
 // digitalWrite(9, LOW);
  //delay(5000);
  
  // Set relay as OUTPUT
  pinMode(relay, OUTPUT);
 
  // By default the relay is off,Check your board for aactive high or activr low output
  digitalWrite(relay, HIGH);
  
  // Initializing serial commmunication    
  Serial.begin(9600); 
  SIM900.begin(9600);
 
  // Give time to your GSM shield log on to network
  delay(20000);
  Serial.print("SIM900 is ready to send receive sms");

  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(1000);
  // Set module to send SMS data to serial out upon receipt 
 SIM900.print("AT+CNMI=2,2,0,0,0\r\n");
  delay(1000);
}
 
void loop(){
  if(SIM900.available()>0){
    textMessage = SIM900.readString();
    Serial.print(textMessage);    
    delay(10);
  } 
 /* if(textMessage.indexOf("CMTI")>=0)
  {
    SIM900.println("AT+CMGR=5\r");
    delay(1000);
    textMessage="";
  }*/
  if(textMessage.indexOf("ON")>=0){
    // Turn on relay and save current state
    digitalWrite(relay, HIGH);
    lampState = "on";
    Serial.println("Relay set to ON");  
    textMessage = "";  
    delSMS(); 
  }
  if(textMessage.indexOf("OFF")>=0){
    // Turn off relay and save current state
    digitalWrite(relay, LOW);
    lampState = "off"; 
    Serial.println("Relay set to OFF");
    textMessage = ""; 
delSMS();
  }
  if(textMessage.indexOf("STATE")>=0){
    String message = "Lamp is " + lampState;
    sendSMS(message);
    Serial.println("Lamp state resquest");
    textMessage = "";
delSMS();
  }
}  
 
// Function that sends SMS
void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(1000);
 
  // change to your sim900's your phone number
  SIM900.println("AT + CMGS = \"8xxxxxxxx25\""); 
  delay(1000);
  // Send the SMSSSSS
  SIM900.println(message); 
  delay(1000);
 
  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(1000);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);  
}
void delSMS()
{
        SIM900.println("AT+CMGDA=\"DEL ALL\"");


}

