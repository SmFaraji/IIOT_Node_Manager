/***
this is second node code that recieve PIDs data from App and Aplly it to system
#telegram channel     -> t.me/EngineeringLab
#aparat channel       -> www.aparat.com/EngineeringLab
#youtube channel      -> https://www.youtube.com/@sm_faraji
#GitHub               -> https://github.com/SmFaraji

***/

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

////////////////////////////////OLED////////////////////////////////////
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
  
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
  
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
/////////////////////////////////////////////////////////////////////////

WiFiUDP Udp;
unsigned int UdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
int sensorValue = 0;
const int analogInPin = A0;
char buffer[40];

String strCon;

    String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void setup()
{  
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("SM_FARAJI", "1*4=1400");
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


  /////////////////////////Setup OLED///////////
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
      Serial.println(F("SSD1306 allocation failed"));
      for(;;);
    }
    delay(1000);
    display.clearDisplay();
  
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("PID TUNER");
    display.display(); 
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
    //Serial.println(incomingPacket);
    strCon = incomingPacket;
    String Kp = getValue(strCon, 'S', 0);
    String Ki = getValue(strCon, 'S', 1);
    String Kd = getValue(strCon, 'S', 2);

    Serial.println("Kp:" +Kp);
    Serial.println("Ki:" + Ki);
    Serial.println("Kd:" + Kd);
    Serial.println("");

    display.clearDisplay();
  
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("Kp:"+Kp);
    display.println("Ki:"+Ki);
    display.println("Kd:"+Kd);
    display.display(); 

   delay(400);
}
