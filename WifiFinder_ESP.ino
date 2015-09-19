/*
 *WiFiFinder ESP8266 
 * by Andres Sabas
 * The Inventor's House Hackerspace
 * 19 sept 2015
 */
 
#include "ESP8266WiFi.h"

// Time to sleep (in seconds):
const int sleepTimeS = 30;

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  pinMode(4, OUTPUT);
  Serial.println("Setup done");

}
  
void loop() {
  uint8_t sec;
  
  analogWrite(4, 10);

  Serial.print(F("Scanning..."));
  int n = WiFi.scanNetworks(); // WiFi.scanNetworks will return the number of networks found
  Serial.println(F("scan done"));
  if (n == 0)
    Serial.println(F("no networks found"));
  else
  {
    Serial.print(n); Serial.print(F(" network"));
      if(n > 1) Serial.print('s');
      Serial.println(F(" found:"));
    for (int i = 0; i < n; ++i)
    {
      int sec = WiFi.encryptionType(i);
      
        // Print SSID and RSSI for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println(sec);
        delay(10);

        if((sec == ENC_TYPE_NONE || sec == ENC_TYPE_WEP) && (WiFi.RSSI(i) > -95)) { // If open network and good signal...
            // Switch LED to conspicuous 'open networks' flash immediately
            analogWrite(4, 1023); // 1 sec
            delay(1000);
            // "Open hotspot" is as good as the indicator gets and the scan
            // can stop now, get into power-saving sleep mode ASAP.
            // If you're using the Serial console and want to see all
            // networks displayed, comment out this line:
            //Serial.println("Not security");
            //Mode Sleep for ESP8266 Version 12 or model with pin16 avaible
            //Necesary jump RST and GPIO16
            
            sleep_now(); // Function Sleep 30 seconds
        }
    }
  }

}

//Mode Sleep for ESP8266 Version 12 or model with pin16 avaible

void sleep_now(){
 
  Serial.print(F("Sleeping..."));
  // deepSleep time is defined in microseconds. Multiply
  // seconds by 1e6 
  ESP.deepSleep(sleepTimeS * 1000000);
}

