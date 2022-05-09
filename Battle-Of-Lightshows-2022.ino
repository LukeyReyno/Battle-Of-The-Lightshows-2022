#include <esp_now.h>
#include <WiFi.h>
#include <FastLED.h>
#include "Music_LED_Matrix_ESPNOW.h"

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
    memcpy(&myData, incomingData, sizeof(myData));
    newData = true;
}

void milli_delay(int thisLong)
{
    int target = millis() + thisLong;
    while (millis() < target) {;}
}

void setup()
{
    Serial.begin(115200);
    Serial.print("\nLukey Reyno Serial Monitor Output for Battle of the Light Show 2022\n");

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    //print the WiFi MAC address
    Serial.print(F("\r\n\nThis node's WiFi MAC Address is "));
    Serial.print(WiFi.macAddress());

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println(F("Error initializing ESP-NOW"));
        return;
    }
    
    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);   
}

void loop()
{
    uint16_t potRead = analogRead(POT_PIN);

    uint8_t brightness = map(potRead, 0, 4095, 0, 150);
    musicMatrix.setBrightness(brightness);

    if (newData)
    {
        //clear flag
        newData = false;

        if (myData.packetVersion != MY_PACKET_VERSION) return;
        
        //process only the pattern numbers implemented.
        //if a pattern is not implemented, turn the display off
        //this inludes pattern 0.
        switch (myData.pattern)
        {
            case 0:
                musicMatrix.turnOff();
                Serial.print(F("packetVersion: "));    Serial.println(myData.packetVersion);
                Serial.print(F("pattern: "));          Serial.println(myData.pattern);
                Serial.print(F("brightness: "));       Serial.println(myData.brightness);
                Serial.print(F("monoAverage: "));      Serial.println(myData.monoAverage);
                Serial.print(F("softpot: "));          Serial.println(myData.softpot);
                Serial.print(F("channelData: "));      for(int i=0; i<7; i++) Serial.printf("%hu ", myData.channelData[i]);
                Serial.println();
                break;

            //RGB, No Peak Hold, Channel Select
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                break;
                
            //RGB, No Peak Hold, Average
            case 8:
                break;

            //Blue, No Peak Hold, Channel Select
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
                break;
                
            //RGB, No Peak Hold, Average
            case 16:
                break;

            //RGB, Peak Hold, Channel Select
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
                break;

            //RGB, Peak Hold, Average
            case 24:
                break;

            //Blue, Peak Hold, Channel Select
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
                break;

            //Blue, Peak Hold, Average
            case 32:
                break;

            //RGB, Peak Only, Channel Select
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 38:
            case 39:
                break;

            //RGB, Peak Only, Average
            case 40:
                break;

            //Best in show
            case 255:
                break;

            default:
                musicMatrix.turnOff();
                break;
        }
    }
}
