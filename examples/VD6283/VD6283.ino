#include "6283a1_light_sensor-class.h"

VD6283TX myColorSensor;

void setup() {
  myColorSensor.begin(Wire);
  myColorSensor.SetExposureTime(100000);
  uint32_t exp;
  myColorSensor.GetExposureTime(uint32_t *exp);
  println(exp);
  myColorSensor.Start(VD6283TX_MODE_CONTINUOUS);
}

void loop() {

}