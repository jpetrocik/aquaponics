#include <ESP8266WiFi.h>

#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <Ticker.h>
#include <ESP8266mDNS.h>

#include "pump.h"
#include "timer.h"

//configuration
#define BUTTON_0 0
#define RELAY_2 5
#define BUTTON_1 9
#define CASE_SWITCH 10
#define RELAY_1 12
#define LED_BLUE 13

//Control variables
int remainingTime = 0;
int nextStart = 0;
int pumpStatus = 0;
bool shouldAccessPointConfig = false;

char hostname[41] = "aquaponics";

Ticker ticker;

Pump pump(RELAY_1);
PumpTimer timer;

void setup()
{

  Serial.begin(115200);

  Serial.println("Aquaponics Firmware");
  Serial.println(__DATE__ " " __TIME__);
  Serial.println(hostname);

  pinMode(LED_BLUE, OUTPUT);

  ticker.attach(0.6, tick);

  wifiSetup();

  mdnsSetup();

  ticker.detach();
  
  otaSetup();

  webServerSetup();

  timer.control(&pump, 15 * 60 * 1000, 45 * 60 * 1000);

  digitalWrite(LED_BLUE, !false);

}

void startPump() {
  pumpStatus = pump.start();
}

void stopPump() {
  pumpStatus = pump.stop();
}

void loop()
{
  timer.update();
  pump.update();

  remainingTime = timer.remainingTime();
  nextStart = timer.nextStart();
  pumpStatus = (int)pump.status();

  
  otaLoop();

  webServerLoop();

}

void factoryReset() {
  Serial.println("Restoring Factory Setting....");
  WiFi.disconnect();
  //SPIFFS.format();
  delay(500);
  Serial.println("Restarting....");
  ESP.restart();
}

void tick() {
  int state = digitalRead(LED_BLUE);
  digitalWrite(LED_BLUE, !state);
}


