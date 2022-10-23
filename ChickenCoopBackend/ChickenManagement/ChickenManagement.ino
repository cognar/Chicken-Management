#include "DHT.h"

#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include "WiFiClient.h"

#define DHTPin 5

#define DHTType DHT22

DHT dht(DHTPin, DHTType);


// WiFi parameters to be configured
const char* ssid = "HoneysHedonistHellscape"; // Write here your router's username
const char* password = "honeytumtum"; // Write here your router's passward


void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
     dht.begin();
  }
  Serial.print("Connected to ");
  Serial.print(ssid);
  Serial.print(" with IP ");
  Serial.println(WiFi.localIP());
}

void loop() {
  String serverPath = "http://192.168.1.152:8090/post";
//  if(WiFi.status() == WL_CONNECTED){
//    WiFiClient client;
//    HTTPClient http;
//    http.begin(client, serverPath.c_str());
//    int httpCode = http.GET();
//    
//    if (httpCode > 0) {
//      String payload = http.getString();
//      Serial.println(payload);
//    }
//    else {
//      Serial.println("Error");
//      Serial.println(httpCode);
//    }
//    
//    http.end();
//  }
//  delay(5000);
  if(WiFi.status() == WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    http.begin(client, serverPath.c_str()); 
    http.addHeader("Content-Type", "text/plain");
    String IATemp = String(ReadTemp());
    int httpResponseCode = http.POST(IATemp);
    Serial.println(IATemp);
    Serial.println(httpResponseCode);    
    http.end();
  }

  delay(5000);
}
  //Variables
    //Boolean states
      //HeatLampState (1 = on, 0 = off)
      //DoorState (1 = open, 0 = closed)
      //FanState (1 = on, 0 = off)
      //TempLoAlert (1 = on, 0 = off)
      //TempHiAlert (1 = on, 0 = off)
      //DoorManualOverride (1 = on, 0 = off)
      //DamperStatus (1 = open, 0 = closed)
      //FanStatus (1 = on, 0 = off)
    //Process Variables
      //InsideTemp
      //OutsideTemp
      //InsideHum
      //OutsideHum
      //Time
    //Setpoints
      //InsideTempHi
      //InsideTempLo
      //InsideHumHi
      //InsideHumLo
      //LoTempAlertDelay

  //Logic    
  //Check Inside and Outside Temperature
    //If InsideTemp < InsideTempLo 
      //**Add logic to bring in Outside air if OA is hotter that IA
      //If HeatLamp = on
        //Begin timer for LoTempAlertDelay
          //If InsideTemp < InsideTempLo after delay
            //TempLoAlert = 1
    //if InsideTemp > InsideTempHi
      //if InsideTemp > OutsideTemp
        //Bring in outside air
        //else TempHiAlert = 1
   //Check Time
     // if (Time > DoorOpenTime and Time < DoorCloseTime) and (DoorState = 0)
        // ChangeDoorState()
   //Check Alerts
     // Interate through alert states and push to web interface
   //Check webserver for any setpoint changes
    //if any discrepencies are found update values in program


float ReadTemp(){
  delay(500); //Delay 500ms to not poll sensor too quickly
  float Temp = dht.readTemperature(true); //Return temperature in fahrenheit
  return Temp;
}

float ReadHum(){
  delay(500); //Delay 500ms to not poll sensor too quickly
  float Hum = dht.readHumidity();
  return Hum;
}
/*
void ChangeHeatLampState(HeatLampState){
  if (HeatLampState){
    //Turn off heatlamp
  }
  else{
    //Turn on heatlamp
  }
  
}

void ChangeDoorState(DoorState){

  
}
*/
