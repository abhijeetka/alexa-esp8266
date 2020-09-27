//
// Program by: Abhijeet
// Email: abhijeet.kamble619@gmail.com
//
//

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>


// -------- WIFI INFORMATION -----
const char *WIFI_SSID = "---ssid----";
const char *WIFI_PASSWORD = "-----password-----";

void bedroomLightChange(EspalexaDevice* dev);
Espalexa espalexa;
EspalexaDevice* bedroomLight;


// TO Control Lights
int bedroomLightPin=5; // D1


void connectToWiFi(){
  
      // This function will try to connect to WIFI
      Serial.println(" Trying to connect to WiFi..");
      Serial.println(WIFI_SSID);
      
      WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
    
      // try only for 15 times and then take a pause.
      int retries = 0;
      while(WiFi.status() != WL_CONNECTED && retries < 15) {
        delay(500);
        Serial.print(".");
        retries++;  
      }
    
        Serial.println("WiFi Connected");
        Serial.println("IP Address: ");
        Serial.println(WiFi.localIP());

        digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
        delay(10); // wait for a second
        digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
        delay(5);
}

void bedroomLightChanged(EspalexaDevice* d){
    if (d == nullptr) Serial.println("Sorry No device Found");
    if(d->getValue()){
        //Tune on the device
        digitalWrite(bedroomLightPin,HIGH);
        d->setValue(127);
        Serial.println("Turned on the light");
    }else{
      // Turn off the device
      digitalWrite(bedroomLightPin, LOW);
      d->setValue(0);
      Serial.println("Turned off the light");  
    }
     
    
}

void lightsInitalize(){

     // Setup the inbuilt LED Pin
     pinMode(LED_BUILTIN, OUTPUT); 
     // Low BedroomLight_01
     pinMode(bedroomLightPin,OUTPUT);
     digitalWrite(bedroomLightPin,LOW);

}

void setup() {
  Serial.begin(9600);
  lightsInitalize();
  connectToWiFi();
  bedroomLight = new EspalexaDevice("Bedroom Light", bedroomLightChanged,EspalexaDeviceType::dimmable);
  espalexa.addDevice(bedroomLight);
  espalexa.begin();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  espalexa.loop();
  delay(1);

}