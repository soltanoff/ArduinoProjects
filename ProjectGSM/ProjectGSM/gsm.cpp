/* ========================================================================= */
#include "gsm.h"
/* ========================================================================= */
SoftwareGSM::SoftwareGSM(short rx, short tx, long serial_port)
{
	this->_rx_pin = rx;
	this->_tx_pin = tx;
	this->_serial_port = serial_port;

	this->_gsm_serial = new SoftwareSerial(_rx_pin, _tx_pin);
	this->_gsm_serial->begin(this->_serial_port);  // Скорость порта для связи Arduino с GSM модулем
	
	this->_speaker = new SoftwareSpeaker();
	this->_speaker->module_initional();
	delay(1000);

	/*
	Serial.println(this->_rx_pin);
	Serial.println(this->_tx_pin);
	Serial.println(this->_serial_port);
	Serial.println(serial_port);
	*/
}
/* ========================================================================= */
void SoftwareGSM::send_sms(const char *phone_number, const char *text)
{
	Serial.println("AT+CMGF=1");
	delay(2000);

	Serial.print("AT+CMGS=\"");
	Serial.print(phone_number);
	Serial.write(0x22);
	Serial.write(0x0D);	// hex код возврата коректки 
	Serial.write(0x0A);	// hex код новой строки

	// delay(2000);
	Serial.print(text);
	delay(500);

	Serial.println(char(26));	// ASCII код Сtrl+Z
	delay(1000);

	Serial.println("AT+CMGF=0");
	this->_speaker->sms_sending();
}
/* ========================================================================= */
void SoftwareGSM::call_number(const char *phone_number)
{
	Serial.print("ATD");
	Serial.println(phone_number);
	// Serial.println(";");
	delay(10000);
	Serial.println("ATH");
}
/* ========================================================================= */
void SoftwareGSM::execute()
{
	// Serial.println(this->_gsm_serial->available());
	if (this->_gsm_serial->available())
	{
		Serial.write(this->_gsm_serial->read());
		// this->_speaker->serial_answear();
	}
	if (Serial.available())
	{
		this->_gsm_serial->write(Serial.read());
		// this->_speaker->serial_sending();
	}
}
/* ========================================================================= */
