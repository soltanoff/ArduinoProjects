#ifndef BLINKING_H
#define BLINKING_H
/* ========================================================================= */
#include "Arduino.h"
/* ========================================================================= */
const int DEFAULT_TIME = 6000;
int TIME;
short PROFILE = 0;
/* ========================================================================= */
void runBlinkMainLed(int pause)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(pause);
  digitalWrite(LED_BUILTIN, LOW);
  delay(pause);
}

void body(int pause, short profileModificator=1)
{
  runBlinkMainLed(pause);
  TIME -= 2 * pause;
  if (TIME < 0)
  {
    TIME = DEFAULT_TIME;
    PROFILE += profileModificator;
  }
}

void blinkQuery(int from, int to, int pause=500)
{
  int decr = from < to ? 1: -1;
  for (int i = from; from < to ? i < to: i >= to; i += decr)
  {
    digitalWrite(leds[i], HIGH);
    delay(pause);
    digitalWrite(leds[i], LOW);
    delay(pause);
  }
}

void blinkAll(int pause=500)
{
  for (unsigned int i = 0; i < sizeof(leds)/sizeof(int); i++)
  {
    for (unsigned int j = 0; j < sizeof(leds)/sizeof(int); j++)
      digitalWrite(leds[j], HIGH);

    delay(pause);

    for (unsigned int j = 0; j < sizeof(leds)/sizeof(int); j++)
      digitalWrite(leds[j], LOW);

    delay(pause);
  }
}
/* ========================================================================= */
#endif /* BLINKING_H */
