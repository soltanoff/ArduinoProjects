/* ========================================================================= */
#ifndef GSM_H
#define GSM_H
/* ========================================================================= */
#include "Arduino.h"
#include "speaker.h"
#include <SoftwareSerial.h>
/* ========================================================================= */
#define DEFAULT_RX 10
#define DEFAULT_TX 11
#define DEFUALT_POWER_PIN 3
#define DEFAULT_SERIAL_PORT 9600
/* ========================================================================= */
class SoftwareGSM
{
private:
	SoftwareSpeaker *_speaker;
	String _serial_buf;

	bool _is_server_connect;
	bool wait_ok_status(const char* command);
	bool wait_answer(const char* command);
	void remove(String& str, char symbol);
	void prepare_buf();
	// void prepare_answer(const char* command);
	// void read_serial(String &value, SoftwareSerial &serial);
public:
	SoftwareSerial *_gsm_serial;
	SoftwareGSM(
		const short& rx = DEFAULT_RX,
		const short& tx = DEFAULT_TX,
		const long& serial_port = DEFAULT_SERIAL_PORT
	);
	void send(String &command);
	void send_answer(String &answer);
	void send_sms(const char* phone_number, const char* text);
	void call_number(const char* phone_number);

	void connect_to_server(const char* ip, const char* port);
	void disconnect_server();

	void execute();
};
/* ========================================================================= */
#endif /* GSM_H */
/* ========================================================================= */
