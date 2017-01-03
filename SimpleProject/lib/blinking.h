#ifndef BLINKING_H
#define BLINKING_H
/* ========================================================================= */
#include "Arduino.h"
/* ========================================================================= */
const int DEFAULT_TIME = 6000;
int TIME;
short PROFILE = 0;
/* ========================================================================= */
class SoftwareBlinking
{
private:
  void body(int pause, short profileModificator=1);
public:
  SoftwareBlinking() {};
  void runBlinkMainLed(int pause);
  void blinkQuery(int from, int to, int pause=500);
  void blinkAll(int pause=500);
};
/* ========================================================================= */
#endif /* BLINKING_H */
