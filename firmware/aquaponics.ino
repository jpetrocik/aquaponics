#include "application.h"
#include "pump.h"
#include "timer.h"
#include "temperature.h"
#include "dht.h"
#include "heater.h"

//Control variables
int airTemp=0;
int humidity=0;
int waterTemp=0;
int remainingTime=0;
int nextStart=0;
int heaterStatus=0;
int pumpStatus=0;

Pump pump(A6);
PumpTimer timer;
Temperature temperature;
DHT dht(D3, DHT11);
Heater heater(A4, 12, 14);

void setup()
{
  timer.control(&pump, 3*60*1000, 180*60*1000);

  temperature.init();

  //expose variables
  Spark.variable("humidity", &humidity, INT);
  Spark.variable("air", &airTemp, INT);
  Spark.variable("water", &waterTemp, INT);
  Spark.variable("timer", &remainingTime, INT);
  Spark.variable("nextStart", &nextStart, INT);
  Spark.variable("heaterStatus", &heaterStatus, INT);
  Spark.variable("pumpStatus", &pumpStatus, INT);


  //expose functions
  Particle.function("pumpOn", startPump);
  Particle.function("pumpOff", stopPump);
}

int startPump(String extra) {
  pump.start();
  return 0;
}

int stopPump(String extra) {
  pump.stop();
  return 0;
}

void loop()
{
  timer.update();
  pump.update();
  temperature.update();

  remainingTime = timer.remainingTime();
  nextStart = timer.nextStart();
  waterTemp = (int)temperature.read();
  humidity = (int)dht.readHumidity();
  airTemp = (int)dht.readTemperature();
  pumpStatus = (int)pump.status();

  heater.update(waterTemp);

  heaterStatus = heater.status();
}
