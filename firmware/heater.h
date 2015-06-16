#ifndef Heater_h
#define Heater_h

#include "application.h"

#define HEATER_ON  1
#define HEATER_OFF 0

class Heater
{
public:
  Heater(int pin, int low, int high);
  int status();
  void update(int waterTemp);
private:
  int _pin;
  int _status;
  int _low;
  int _high;
};

Heater::Heater(int pin, int low, int high){
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  _status = PUMP_OFF;
  _low = low;
  _high = high;
}

int Heater::status(){
  return _status;
}

void Heater::update(int waterTemp){
  if (waterTemp <= _low && !_status) {
    digitalWrite(_pin, HIGH);
    _status = HEATER_ON;
  } else if (waterTemp >= _high && _status) {
    digitalWrite(_pin, LOW);
    _status = HEATER_OFF;
  }
}

#endif
