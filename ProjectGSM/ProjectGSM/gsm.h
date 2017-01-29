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
const short DEFUALT_POWER_PIN = 3;
const long DEFAULT_SERIAL_PORT = 9600;
/* ========================================================================= */
class SoftwareGSM
{
private:
	short _rx_pin;
	short _tx_pin;
	long _serial_port;
	SoftwareSerial *_gsm_serial;
	SoftwareSpeaker *_speaker;
	String _serial_buf;

	bool _is_server_connect;
public:
	SoftwareGSM(
		short rx = DEFAULT_RX,
		short tx = DEFAULT_TX,
		long serial_port = DEFAULT_SERIAL_PORT
	);
	void send(String &command);
	
	void send_sms(const char *phone_number, const char *text);
	void call_number(const char *phone_number);
	
	void connect_to_server(String ip, String port);
	void disconnect_server();

	void execute();
};
/* ========================================================================= */
#endif /* GSM_H */
/* ========================================================================= */