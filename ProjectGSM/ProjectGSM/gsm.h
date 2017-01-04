/* ========================================================================= */
#ifndef GSM_H
#define GSM_H
/* ========================================================================= */
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "speaker.h"
/* ========================================================================= */
const short DEFAULT_RX = 10;
const short DEFAULT_TX = 11;
const long DEFAULT_SERIAL_PORT = 115200;
/* ========================================================================= */
class SoftwareGSM
{
private:
	short _rx_pin;
	short _tx_pin;
	long _serial_port;
	SoftwareSerial *_gsm_serial;
	SoftwareSpeaker *_speaker;
public:
	SoftwareGSM(
		short rx = DEFAULT_RX,
		short tx = DEFAULT_TX,
		long serial_port = DEFAULT_SERIAL_PORT
	);
	void send_sms(const char *phone_number, const char *text);
	void call_number(const char *phone_number);
	void execute();
};
/* ========================================================================= */
#endif /* GSM_H */
/* ========================================================================= */