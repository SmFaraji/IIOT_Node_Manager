/***
this is first node code that recieve commands and send sensor data via udp connection with central node(B4A App)
#telegram channel     -> t.me/EngineeringLab
#aparat channel       -> www.aparat.com/EngineeringLab
#youtube channel      -> https://www.youtube.com/@sm_faraji
#GitHub               -> https://github.com/SmFaraji

***/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

WiFiUDP Udp;
unsigned int UdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
int sensorValue = 0;
const int analogInPin = A0;
char buffer[40];

String strCon;


void setup()
{
  pinMode(0, OUTPUT);
  //digitalWrite(0, HIGH); //turn off led
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("SM_FARAJI", "seyed1*4=1400");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Udp.begin(UdpPort);
 }


void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.println(incomingPacket);
    strCon = incomingPacket;

    if (strCon=="A1On") {
      digitalWrite(5, HIGH);
    }
    else if (strCon=="A1Off") {
      digitalWrite(5, LOW);
    } 
    if (strCon=="A2On") {
      digitalWrite(4,HIGH);
    }
    else if (strCon=="A2Off") {
      digitalWrite(4,LOW);
    } 
    if (strCon=="A3On") {
      digitalWrite(0, HIGH);
    }
    else if (strCon=="A3Off") {
      digitalWrite(0, LOW);
    } 
  }
    sensorValue = analogRead(analogInPin);
    sensorValue = map(sensorValue, 0, 1023, 0, 200);
    sprintf(buffer, "%d", sensorValue); //Value: 
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(buffer);
    Udp.endPacket();
    Serial.println(buffer);

   delay(400);
}
