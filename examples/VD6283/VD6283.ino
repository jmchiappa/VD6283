#include "6283a1_light_sensor-class.h"

VD6283::VD6283TX myColorSensor;

#define print2ln(a,b)   {Serial.print(a);Serial.print('\t');Serial.println(b);}
#define scopeChannel(a,b)   {Serial.print(a);Serial.print(':');Serial.println(b);}
#define GAIN(a)         (uint16_t)((float)a*256)
#define GAIN_NOMINAL 50
const uint8_t gain[] = {
  GAIN_NOMINAL, // rouge
  GAIN_NOMINAL, // visible
  GAIN_NOMINAL, // bleu
  GAIN_NOMINAL*3/5, // vert
  GAIN_NOMINAL, // IR
  GAIN_NOMINAL // tout
};

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  print2ln("begin =",myColorSensor.begin(Wire));
  print2ln("readID=",myColorSensor.ReadID());
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
      scopeChannel( label[i] , (float)(( (float)measure[i] / measure[VD6283::CHANNEL::VISIBLE] )*100) );
      if(i!=5)
        Serial.print(",");
    }
    Serial.println();
  }
}