/* ========================================================================= */
#ifndef SPEAKER_H
#define SPEAKER_H
/* ========================================================================= */
#include "Arduino.h"
/* ========================================================================= */
class SoftwareSpeaker
{
private:
  short _pin;
  void speaker_voice(int time=500, int iteration=1, int frequency=0);
public:
  SoftwareSpeaker(short pin=2);
  void module_initional();
};
/* ========================================================================= */
#endif /* SPEAKER_H */
/* ========================================================================= */

