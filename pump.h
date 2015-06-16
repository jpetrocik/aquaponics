#ifndef Pump_h
#define Pump_h

#include "application.h"

#define PUMP_ON  1
#define PUMP_OFF 0

class Pump
{
public:
  Pump(int pin);
  void start();
  void start(long ms);
  void stop();
  int status();
  void update();
private:
  int _pin;
  long _stopTime;
  int _status;
};

Pump::Pump(int pin){
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  _status = PUMP_OFF;
  _stopTime = 0;
}

void Pump::start(){
  start(0);
}

void Pump::start(long ms){
  digitalWrite(_pin, HIGH);
  _status = PUMP_ON;
  _stopTime = (ms > 0)?millis()+ms:0;

}

void Pump::stop(){
  digitalWrite(_pin, LOW);
  _status = PUMP_OFF;
}

int Pump::status(){
  return _status;
}

void Pump::update(){
  if (_status == PUMP_ON){

    if (_stopTime > 0 && _stopTime < millis()) {
      stop();
    }

  }
}

#endif
