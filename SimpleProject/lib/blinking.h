#ifndef BLINKING_H
#define BLINKING_H
/* ========================================================================= */
#include "Arduino.h"
/* ========================================================================= */
const int DEFAULT_TIME = 6000;
int TIME;
short PROFILE = 0;
/* ========================================================================= */
void runBlink(int pause)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(pause);
  digitalWrite(LED_BUILTIN, LOW);
  delay(pause);
}

void body(int pause, short profileModificator=1)
{
  runBlink(pause);
  TIME -= 2 * pause;
  if (TIME < 0)
  {
    TIME = DEFAULT_TIME;
    PROFILE += profileModificator;
  }
}
/* ========================================================================= */
#endif /* BLINKING_H */
