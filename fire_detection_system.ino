// Include Software Serial library to communicate with GSM
#include <SoftwareSerial.h>
//connect the Tx pin of SIM900A module with digital pin and RX pin with digital pin 8
SoftwareSerial SIM900(7, 8); 

// Variable to store text message
String message;

int flamesensor=2; //Connect flame sensor with Digital pin 2 of the Arduino
int buzzer=3;  /// Connect the buzzer with Digital pin 3 of the Arduino
void setup()
{
  Serial.begin(19200);// initialize serial communication @ 9600 baud:
  pinMode(flamesensor, INPUT); 
  pinMode(buzzer, OUTPUT);
  SIM900.begin(19200);
  // Give time to your GSM shield log on to network
  delay(20000);
  Serial.print("SIM900 ready...");
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  // Set module to send SMS data to serial out upon receipt 
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}
void loop()
{
  
  if (digitalRead(flamesensor) == HIGH )
  {
    digitalWrite(buzzer, HIGH); // Led ON
    Serial.println("** Fire detected!!! **");
    digitalWrite(buzzer,HIGH);
    message = "Fire detected";
    sendSMS(message);
    delay(5000);
  }
  else
  {
    digitalWrite(buzzer, LOW); 
    Serial.println("No Fire detected");
  }
  delay(100);
}

// Function that sends SMS
void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS Replace X with your number
  SIM900.println("AT + CMGS = \"+92XXXXXXXXX\""); 
  delay(100);
  // Send the SMS
  SIM900.println(message); 
  delay(100);
  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);  
}
