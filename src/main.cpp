
#include <WiFi.h>
#include <SPIFFS.h>
#include <Arduino.h>
#include <IRremote.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <cppQueue.h>
// #include <remotes/Samsung.h>
// #include <remotes/HDMI_Switch.h>
#include <remotes.h>
#include <secrets.h>

#define IR_RECEIVE_PIN 23
#define IR_SEND_PIN 21

#define DELAY_AFTER_SEND 2000
#define DELAY_AFTER_LOOP 5000

AsyncWebServer server(80);
cppQueue queue(sizeof(RemoteButton), 10, LIFO);

bool requestProcessing = false;
int ledStatus = LOW;

void toggleLED()
{
    ledStatus = ledStatus == LOW ? HIGH : LOW;

    digitalWrite(BUILTIN_LED, ledStatus);
}

void ledOn()
{
    ledStatus = HIGH;

    digitalWrite(BUILTIN_LED, ledStatus);
}

void ledOff()
{
    ledStatus = LOW;

    digitalWrite(BUILTIN_LED, ledStatus);
}

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("Connected to AP successfully!");
}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    ledOff();

    Serial.println("Disconnected from WiFi access point");
    Serial.print("WiFi lost connection. Reason: ");
    Serial.println(info.disconnected.reason);
    Serial.println("Trying to Reconnect");

    WiFi.begin(WIFI_SSID, WIFI_PW);

    while (WiFi.status() != WL_CONNECTED)
    {
        toggleLED();
        Serial.print(".");
        delay(500);
    }
}

void setupWifi()
{
    WiFi.onEvent(WiFiStationConnected, SYSTEM_EVENT_STA_CONNECTED);
    WiFi.onEvent(WiFiGotIP, SYSTEM_EVENT_STA_GOT_IP);
    WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PW);

    while (WiFi.status() != WL_CONNECTED)
    {
        toggleLED();
        Serial.print(".");
        delay(500);
    }
}

int findButtonIndex(RemoteButton const remoteBtns[], int size, String btn)
{
    for (int i = 0; i < size; i++)
    {
        if (remoteBtns[i].btn == btn)
        {
            return i;
        }
    }

    return -1;
}

void setup()
{
    Serial.begin(9600);
    pinMode(BUILTIN_LED, OUTPUT);

    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);

    delay(10);
    setupWifi();

    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.on("/api/hdmi-switcher", HTTP_GET, [](AsyncWebServerRequest *request)
              { 
                if (request->hasParam("btn")) 
                {
                    AsyncWebParameter *btn = request->getParam("btn");

                    int i = findButtonIndex(HDMISwitcher, 5, btn->value());

                    if (i >= 0)
                    {
                        queue.push(&HDMISwitcher[i]);
                        request->send(200, "application/json", "{\"success\": true}");
                        return;
                    }

                    request->send(400, "application/json", "{\"error\": \"Unknown button.\"}");
                    return;
                }

                    request->send(400, "application/json", "{\"error\": \"Missing button.\"}"); });

    server.on("/api/samsung", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("btn"))
        {
            AsyncWebParameter *repeat = request->getParam("repeat");
            AsyncWebParameter *btn = request->getParam("btn");

            int i = findButtonIndex(SamsungRemote, 43, btn->value());
            int repeatTimes = 1;

            if (i >= 0)
            {
                if (request->hasParam("repeat")) {
                    repeatTimes = repeat->value().toInt();

                    if (repeatTimes < 1 && repeatTimes > 10)
                    {
                        repeatTimes = 1;
                    }
                }

                if (SamsungRemote[i].repeatable == false)
                {
                    repeatTimes = 1;
                }

                for (size_t n = 0; n < repeatTimes; n++)
                {
                    queue.push(&SamsungRemote[i]);
                }
                
                request->send(200, "application/json", "{\"success\": true}");
                return;
            }

            request->send(400, "application/json", "{\"error\": \"Unknown button.\"}");
            return;
        }

       request->send(400, "application/json", "{\"error\": \"Missing button.\"}"); });

    server.onNotFound([](AsyncWebServerRequest *request)
                      { 
                          Serial.println(request->url());
                          request->send(404); });

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    server.begin();
}

void loop()
{
    // if (IrReceiver.decode())
    // {
    //     IrReceiver.printIRResultShort(&Serial);
    //     IrReceiver.resume();
    // }

    while (!queue.isEmpty())
    {
        RemoteButton btn;
        queue.pop(&btn);
        Serial.println(btn.btn);

        if (btn.type == NEC_TYPE)
        {
            IrSender.sendNEC(HDMI_SWITCHER_ADDRESS, btn.value, 0);
        }
        else if (btn.type == SAMSUNG_TYPE)
        {
            IrSender.sendSamsung(SAMSUNG_ADDRESS, btn.value, 0);
        }

        delay(200);
    }

    delay(500);
}