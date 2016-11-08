#include "../lib/blinking.h"


int leds[] = {LED_BUILTIN, 10, 11, 12};

void setup()
{
  TIME = DEFAULT_TIME;
  // pinMode(LED_BUILTIN, OUTPUT);
  for (unsigned int i = 0; i < sizeof(leds)/sizeof(int); i++)
    pinMode(leds[i], OUTPUT);
}

void loop()
{
  blinkQuery(0, sizeof(leds)/sizeof(int));
  blinkQuery(sizeof(leds)/sizeof(int) - 1, 0);
  blinkAll();

  /*
  switch (PROFILE) {
    case 0:
      body(100);
      break;
    case 1:
      body(1000, -1);
      break;
  };
  */
}
