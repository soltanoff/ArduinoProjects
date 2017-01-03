/* ========================================================================= */
#include "../libblinking.h"
/* ========================================================================= */
void SoftwareBlinking::runBlinkMainLed(int pause)
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(pause);
  digitalWrite(LED_BUILTIN, LOW);
  delay(pause);
}
/* ========================================================================= */
void SoftwareBlinking::body(int pause, short profileModificator)
{
  runBlinkMainLed(pause);
  TIME -= 2 * pause;
  if (TIME < 0)
  {
    TIME = DEFAULT_TIME;
    PROFILE += profileModificator;
  }
}
/* ========================================================================= */
void SoftwareBlinking::blinkQuery(int from, int to, int pause)
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
/* ========================================================================= */
void SoftwareBlinking::blinkAll(int pause)
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