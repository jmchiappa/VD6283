#include "6283a1_light_sensor-class.h"

VD6283::VD6283TX myColorSensor;

#define print2ln(a,b)   {Serial.print(a);Serial.print('\t');Serial.println(b);}
#define GAIN(a)         (uint16_t)((float)a*256)
#define GAIN_NOMINAL 50
const uint8_t gain[] = {GAIN_NOMINAL,GAIN_NOMINAL,GAIN_NOMINAL,GAIN_NOMINAL*3/5,GAIN_NOMINAL,GAIN_NOMINAL};

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  print2ln("begin =",myColorSensor.begin(Wire));
  uint32_t id;
  print2ln("readID=",myColorSensor.ReadID(&id));
  myColorSensor.SetExposureTime(10000);
  for(uint8_t i=0; i < VD6283::CHANNEL::LENGTH;i++)
    print2ln("gain red=",myColorSensor.SetGain(i,GAIN(gain[i])));

  print2ln("start=",myColorSensor.Start(VD6283::MODE::CONTINUOUS));
}
uint8_t dataReady;
uint32_t measure[6];
const char *label[] = {
  "rouge",
  "visible",
  "bleu",
  "vert",
  "IR",
  "tout"
};

#define VALUE_MAX 16777216.0f
void loop() {
// myColorSensor.isDataReady(&dataReady);
  int ret = myColorSensor.GetValues(measure);
  if(ret != 0) {
    // myColorSensor.GetValues((measure));
    Serial.print("");
    for(uint8_t i=0; i < 6 ; i++ ) {
      Serial.print(label[i]);
      Serial.print(":");
      Serial.print(measure[i]);
      // Serial.print((float)(( (float)measure[i] / VALUE_MAX )*100));
      // Serial.print("");
      if(i!=5)
        Serial.print(",");
    }
    Serial.println();
  }
}