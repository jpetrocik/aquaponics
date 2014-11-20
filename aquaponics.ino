#include "application.h"
#include "pump.h"
#include "timer.h"

//Control variables
int pumpCycle;
int pumpStatus;
int remainingTime;
int nextStart;

Pump pump(7);
Timer timer;

void setup()
{
  timer.control(&pump, 15*60*1000, 45*60*1000);

  //expose functions
  Spark.function("abort", abortAll);

  //expose variables
  Spark.variable("pumpCycle", &pumpCycle, INT);
  Spark.variable("pumpStatus", &pumpStatus, INT);
  Spark.variable("timer", &remainingTime, INT);
  Spark.variable("nextStart", &nextStart, INT);
}

void loop()
{
  timer.update();
  pump.update();

  pumpCycle = timer.counter();
  pumpStatus = pump.status();
  remainingTime = 1 + timer.remainingTime()/60000;
  nextStart = 1 + timer.nextStart()/60000;
}

int abortAll(String command)
{
  pump.stop();
}
