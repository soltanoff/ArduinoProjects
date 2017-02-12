/* ========================================================================= */
#include "gsm.h"
// #include <SoftwareSerial.h>
/* ========================================================================= */
SoftwareGSM *gsm;
/* ========================================================================= */
void setup()
{
	// std::vector<int> f;
	// //std::function<void(int)> f  = [](int a) { return a + 5; };
	// int c = 6; //void (*f)(int)
	// auto f = [&c](int a) { return a + 5; };
	// bind(int(5), c);
	Serial.begin(DEFAULT_SERIAL_PORT);  // Скорость порта для связи Arduino с компьютером
	gsm = new SoftwareGSM();
	digitalWrite(DEFUALT_POWER_PIN, HIGH);
	Serial.println("[GSM] module started.");
}
/* ========================================================================= */
void loop()
{
	gsm->execute();
}
/* ========================================================================= */
