#include "6283a1_light_sensor-class.h"

VD6283::VD6283TX myColorSensor;

#define print2ln(a,b)   {Serial.print(a);Serial.print('\t');Serial.println(b);}
#define GAIN(a)         (uint16_t)((float)a*256)
void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  print2ln("begin =",myColorSensor.begin(Wire));
  uint32_t id;
  print2ln("readID=",myColorSensor.ReadID(&id));
  myColorSensor.SetExposureTime(10000);
  print2ln("gain red=",myColorSensor.SetGain(VD6283::CHANNEL::BLUE, GAIN(100)));
  print2ln("start=",myColorSensor.Start(VD6283::MODE::CONTINUOUS));
}
uint8_t dataReady;
uint32_t measure[6];
#define VALUE_MAX 16777216.0f
void loop() {
// myColorSensor.isDataReady(&dataReady);
  int ret = myColorSensor.GetValues(measure);
  if(ret != 0) {
    // myColorSensor.GetValues((measure));
    for(uint8_t i=0; i < 6 ; i++ ) {
      Serial.print((float)(( (float)measure[i] / VALUE_MAX )*100));
      Serial.print("%");
      Serial.print("\t");
    }
    Serial.println();
  }
}