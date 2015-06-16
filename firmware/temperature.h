#ifndef Temperature_h
#define Temperature_h

#include "application.h"
#include "DS18B20.h"
#include "OneWire.h"

#define READ_DELAY 5000

class Temperature
{
  public:
    void init();
    void update();
    float read();
  private:
    DS18B20 ds18b20 = DS18B20(4);
    long nextRead = 0;
    float currentTemp;
    int sensorFound = true;
};

void Temperature::init(){
  int tries=0;

  while (!ds18b20.search()){
    if (tries++ > 11){
      sensorFound = false;
      break;
    }
    delay(250);
  }
}

void Temperature::update(){
  long now = millis();
  if (sensorFound && now > nextRead){
    currentTemp = ds18b20.getTemperature();
    nextRead = now + READ_DELAY;
  }
}

float Temperature::read(){
   return currentTemp;
}

#endif
