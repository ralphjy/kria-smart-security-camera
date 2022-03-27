#include"DFRobot_LIDAR07.h"

//If using IIC mode, please enable macro USE_IIC
#define USE_IIC
#ifdef USE_IIC  
DFROBOT_LIDAR07_IIC  LIDAR07;
#endif

void setup()
{
  uint32_t version;
  Serial.begin(115200);
  while(!Serial);
  delay(5000);

#ifdef USE_IIC
  while(!LIDAR07.begin()){
    Serial.println("The sensor returned data validation error");
    delay(1000);
  }
#endif
  
  version = LIDAR07.getVersion();
  Serial.print("VERSION: ");
  Serial.print((version>>24)&0xFF,HEX);
  Serial.print(".");Serial.print((version>>16)&0xFF,HEX);
  Serial.print(".");Serial.print((version>>8)&0xFF,HEX);
  Serial.print(".");Serial.println((version)&0xFF,HEX);

  LIDAR07.startFilter();  //After enabling the filter, it can be stopped by calling LIDAR07.stopFilter()
  
}
 
void loop()
{ 
  while(!LIDAR07.startMeasure()){
    Serial.println("Incorrect data was returned");
    delay(1000);
  }
  Serial.print("Distance:");Serial.print(LIDAR07.getDistanceMM());Serial.println(" mm");
//  Serial.print("Amplitude:");Serial.println(LIDAR07.getSignalAmplitude());
  delay(200);
}
