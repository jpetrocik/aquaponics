#ifndef Pump_h
#define Pump_h

#define PUMP_ON  1
#define PUMP_OFF 0

class Pump
{
public:
  Pump(int pin);
  int start();
  int start(long ms);
  int stop();
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

int Pump::start(){
  return start(0);
}

int Pump::start(long ms){
  digitalWrite(_pin, HIGH);
  _status = PUMP_ON;
  _stopTime = (ms > 0)?millis()+ms:0;
  return _status;
}

int Pump::stop(){
  digitalWrite(_pin, LOW);
  _status = PUMP_OFF;
  return _status;
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
