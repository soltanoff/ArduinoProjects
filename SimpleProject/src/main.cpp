#include "../lib/blinking.h"


void setup()
{
  TIME = 6000;
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  switch (PROFILE) {
    case 0:
      body(100);
      break;
    case 1:
      body(1000, -1);
      break;
  };
}
