#include <SoftwareSerial.h>
SoftwareSerial ESP(3, 2); // RX | TX
String command ="";
boolean initialized=false;
String initOrders[] = {"AT+CIPMUX=1", "AT+CIPSERVER=1,80"};

void initializeWifiModule()
{
  int arrayLength = sizeof(initOrders) / sizeof(initOrders[0]);
  for (int i=0;i<arrayLength;i++)
  {
    Serial.print("[+] Sending order: ");
    Serial.print(initOrders[i]);
    delay(1000);
    Serial.print("\n");
    ESP.println(initOrders[i]);
  }
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  ESP.begin(9600);
  pinMode(13, OUTPUT);
  initializeWifiModule();
}

void loop() 
{
  // Repetir lo recibido por el ESP8266 hacia el monitor serial
  if (ESP.available())
  { 
    char c = ESP.read() ;
    Serial.print(c);
    command+=c;
    if (c=='\n')
    {
      Serial.print("Received command: ");
      Serial.print(command);
      Serial.print("\n");
      if (command.indexOf("led")>0)
      {
        digitalWrite( 13, !digitalRead(13)) ;
        Serial.println("Invirtiendo pin 13");
      }
      command="";
    }
  }

     // Repetir lo recibido por el monitor serial hacia el ESP8266
  if (Serial.available())
  {  
    char c = Serial.read();
    ESP.print(c);
  }
}
