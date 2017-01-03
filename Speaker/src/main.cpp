#include <SoftwareSerial.h>
#include "../lib/speaker.h"

SoftwareSpeaker speaker(2);

void setup() 
{
  speaker.module_initional();
  Serial.begin(115200);  // Скорость порта для связи Arduino с компьютером
  Serial.println("This is a simple speaker project!");
}

void loop() 
{
  
}
