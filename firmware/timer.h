#ifndef PumpTimer_h
#define PumpTimer_h

#include "application.h"
#include "pump.h"

class PumpTimer
{
  public:
    PumpTimer();
    void control(Pump* pump, long on, long delay);
    int counter();
    int remainingTime();
    long nextStart();
    void update();
  private:
    Pump* _pump;
    long _on;
    long _delay;
    long _nextStart;
    long _nextStop;
    long _counter;

    void schedule();
};

int convertToMinutes(long millis){
  return 1 + millis/60000;
}

PumpTimer::PumpTimer(){}

void PumpTimer::control(Pump* pump, long on, long delay){
  _pump = pump;
  _on = on;
  _delay = delay;
  _nextStart=millis()+15000; //15sec delay
  _nextStop=_nextStart+_on;
  _counter = 0;
}

int PumpTimer::counter(){
  return _counter;
}

int PumpTimer::remainingTime(){
  int split = _nextStop - millis();

  return (split < _on)?convertToMinutes(split):0;
}

long PumpTimer::nextStart(){
  return (_nextStop < _nextStart)?0:convertToMinutes(_nextStart-millis());
}

void PumpTimer::update(){
  long now = millis();

  /*
   * Starts pump and immediately schedules
   * next start time
   */
  if (_nextStart < now){
    _pump->start();
    _counter++;
    _nextStart += _on + _delay;
  }

  if (_nextStop < now ){
    _pump->stop();
    _nextStop = _nextStart + _on;
  }

}

#endif
