#include <esp_now.h>
#include <WiFi.h>
#include <FastLED.h>
#include "Music_LED_Matrix_ESPNOW.h"

// set up matrix
LED_Matrix musicMatrix;

// initialize data struct
struct_message myData;

const int MY_PACKET_VERSION = 2;    //only processes verion 2 packets
const bool debug_flag = false;
volatile boolean newData = false;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t* mac, const uint8_t *incomingData, int len)
{
    memcpy(&myData, incomingData, sizeof(myData));
    newData = true;
}

void setup()
{
    Serial.begin(115200);
    Serial.print("\nLukey Reyno Serial Monitor Output for Battle of the Light Show 2022\n");

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    //print the WiFi MAC address
    Serial.print(F("\r\n\nThis node's WiFi MAC Address is "));
    Serial.println(WiFi.macAddress());

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println(F("Error initializing ESP-NOW"));
        return;
    }
    
    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);

    musicMatrix.turnOff();
    delay(500);
}

void loop()
{
    if (newData)
    {
        //clear flag
        newData = false;
        musicMatrix.turnOff();

        if (myData.packetVersion != MY_PACKET_VERSION) return;
        
        //process only the pattern numbers implemented.
        //if a pattern is not implemented, turn the display off
        //this inludes pattern 0.

        if (debug_flag)
        {
            Serial.print("Data Pattern: "); Serial.println(myData.pattern);
        }

        switch (myData.pattern)
        {
            // debug pattern
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
                //Bar_Visualizer(&musicMatrix, myData);
                break;

            //Best in show (final submission)
            case 255:
                Bar_Visualizer(&musicMatrix, myData);
                break;

            default:
                //musicMatrix.turnOff();
                musicMatrix.lightOneRow(3, CRGB::AliceBlue);
                break;
        }
        musicMatrix.show();
    }
}
