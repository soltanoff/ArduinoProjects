/* ========================================================================= */
#include "gsm.h"


extern int __bss_end;
extern void *__brkval;
// Функция, возвращающая количество свободного ОЗУ (RAM)
int memoryFree()
{
   int freeValue;
   if((int)__brkval == 0)
      freeValue = ((int)&freeValue) - ((int)&__bss_end);
   else
      freeValue = ((int)&freeValue) - ((int)__brkval);
   return freeValue;
}
void viewFreeMemory()
{
	Serial.print(F("Free RAM: "));
	Serial.println(memoryFree());
}
/* ========================================================================= */
SoftwareGSM::SoftwareGSM(const short& rx, const short& tx, const long& serial_port)
{
	// this->_speaker = new SoftwareSpeaker();
	// this->_speaker->module_initional();
	// delay(1000);

	this->_is_server_connect = false;
	this->_gsm_serial = new SoftwareSerial(rx, tx);

	// Скорость порта для связи Arduino с GSM модулем
	this->_gsm_serial->begin(serial_port);

	// this->A6_command("AT+IPR=" + String(serial_port)., FF(F("OK")), FF(F("yy")), 5000, 2);
	for (short i = 0; i < 5; i++) {
		this->A6_command(FF(F("AT")), FF(F("OK")), FF(F("yy")), 100, 2);
	}
	this->A6_command(FF(F("AT+CMEE=2")), FF(F("OK")), FF(F("yy")), 5000, 2);
	this->A6_command(FF(F("AT+CSCS=\"GSM\"")), FF(F("OK")), FF(F("yy")), 5000, 2);
	this->A6_command(FF(F("AT+CMGF=1")), FF(F("OK")), FF(F("yy")), 5000, 2);
	this->A6_command(FF(F("AT+SNFS=0")), FF(F("OK")), FF(F("yy")), 10000, 2);
	this->A6_command(FF(F("ATE0")), FF(F("OK")), FF(F("yy")), 5000, 2);

}
/* ========================================================================= */
/*
void SoftwareGSM::send_sms(const char* phone_number, const char* text)
{
	this->_gsm_serial->print("AT+CMGS=\"");
	this->_gsm_serial->print(phone_number);
	this->_gsm_serial->write(0x22);
	this->_gsm_serial->write(0x0D);	// hex код возврата коректки
	this->_gsm_serial->write(0x0A);	// hex код новой строки
	// delay(2000);
	this->_gsm_serial->print(text);
	delay(100);
	this->_gsm_serial->println(char(26));	// ASCII код Сtrl+Z
	// delay(1000);
	// this->_speaker->sms_sending();
}
*/
/* ========================================================================= */
/*
void SoftwareGSM::call_number(const char* phone_number)
{
	this->_gsm_serial->print("ATD");
	this->_gsm_serial->println(phone_number);
	delay(10000);
	this->_gsm_serial->println("ATH");
}
*/
/* ========================================================================= */
void SoftwareGSM::remove(String& str, char symbol) {
    while (str.indexOf(symbol) >= 0)
        str.remove(str.indexOf(symbol), 1);
}
void SoftwareGSM::prepare_buf()
{
	remove(_serial_buf, '\r');
    _serial_buf.replace(F("\n\n"), F(" | "));
    remove(_serial_buf, '\n');
}
/* ========================================================================= */
void SoftwareGSM::A6_read() {
	_serial_buf = "";
	if (this->_gsm_serial->available())  {
    	_serial_buf = this->_gsm_serial->readString();
  	}
}
/* ========================================================================= */
byte SoftwareGSM::A6_wait_for(
	const char* response1,
	const char* response2,
	unsigned int& timeOut
) {
  	unsigned long entry = millis();
  	this->A6_read();
	byte retVal = 99;
	do {
		this->A6_read();
	    if (_serial_buf.length()) {
			Serial.print((millis() - entry));
		    Serial.print(F(" ms "));
	    	Serial.println(_serial_buf);
	    }
	}
	while (
		(_serial_buf.indexOf(response1) + _serial_buf.indexOf(response2) == -2)
		&& millis() - entry < timeOut
	);

	if ((millis() - entry) >= timeOut) {
		retVal = TIMEOUT;
	}
	else {
		if (_serial_buf.indexOf(response1) + _serial_buf.indexOf(response2) > -2)
			retVal = OK;
		else
			retVal = NOT_OK;
	}
	//  Serial.print("retVal = ");
	//  Serial.println(retVal);
	return retVal;
}
/* ========================================================================= */
byte SoftwareGSM::A6_command(
	const char* command,
	const char* response1,
	const char* response2,
	unsigned int timeOut,
	int repetitions
) {
	byte returnValue = NOT_OK;
	byte count = 0;
	while (count < repetitions && returnValue != OK) {
		this->_gsm_serial->println(command);
		Serial.print(F("Command: "));
		Serial.println(command);
		if (this->A6_wait_for(response1, response2, timeOut) == OK) {
			// Serial.println("OK");
			returnValue = OK;
		}
		else
			returnValue = NOT_OK;
		count++;
	}
	return returnValue;
}
/* ========================================================================= */
void SoftwareGSM::connect_to_server(const char* ip, const char* port)
{
	Serial.println(F("Connect to server..."));

	// this->wait_ok_status("AT+CGATT?");
	// delay(2000);
	// Прикрепиться сети если 1,
	// открепиться если 0 (длительность: 8 сек)
	/*
	if (_serial_buf.indexOf("+CGATT:0") > -1)
	{
		// this->wait_answer("AT+CGATT=1");  // _gsm_serial->println("AT+CGATT=1");
		Serial.println(_serial_buf);
		delay(20000);
	}
	*/
	// Активируем заданный контекст (длительность: 3-4 сек)
	// 1 - состояние (вкл/выкл)
	// 1 - индентификатор контекста PDP
	// this->wait_ok_status("AT+CGACT=1,1");
	// delay(3000);
	// Задаем контекст поключения PDP (Packet Data Protocol)
	// 1 - индентификатор контекста PDP (max 7)
	// "IP" - тип протокола (PDP type: IP, IPV6, PPP Point to Point Protocol)
	// "cmnet" - имя точки доступа
	// this->wait_ok_status("AT+CGDCONT=1,\"IP\",\"cmnet\"");
	// delay(5000);
	// Начать TCP/UDP подключение
	// (длительность: 2-3 сек)

	this->A6_command(FF(F("AT+CGATT=1")), FF(F("OK")), FF(F("yy")), 10000, 2);
	this->A6_command(FF(F("AT+CGACT=1,1")), FF(F("OK")), FF(F("yy")), 10000, 2);
	_serial_buf = F("AT+CIPSTART=\"TCP\",\"");
	_serial_buf += ip;
	_serial_buf += F("\", ");
	_serial_buf += port;
	this->A6_command(_serial_buf.c_str(), FF(F("OK")), FF(F("yy")), 10000, 2);
	this->A6_command(FF(F("AT+CIPSEND=1, \"2\"")), FF(F("OK")), FF(F("yy")), 10000, 1);
	// wait_ok_status("AT+CIPSEND=4, \"help\"");
	this->_is_server_connect = true;
	/*
	this->_gsm_serial->println("AT+CGATT=1"); // // Прикрепиться сети если 1,
	// открепиться если 0 (длительность: 8 сек)
	delay(8000);
	// Задаем контекст поключения PDP (Packet Data Protocol)
	// 1 - индентификатор контекста PDP (max 7)
	// "IP" - тип протокола (PDP type: IP, IPV6, PPP Point to Point Protocol)
	// "cmnet" - имя точки доступа
	this->_gsm_serial->println("AT+CGDCONT=1,\"IP\",\"cmnet\"");
	delay(10);
	// Активируем заданный контекст (длительность: 3-4 сек)
	// 1 - состояние (вкл/выкл)
	// 1 - индентификатор контекста PDP
	this->_gsm_serial->println("AT+CGACT=1,1");
	delay(10);
	// Начать TCP/UDP подключение
	// (длительность: 2-3 сек)
	this->_gsm_serial->println("AT+CIPSTART=\"TCP\",\"" + ip + "\", " + port);
	delay(3000);
	this->_gsm_serial->println("AT+CIPSEND=4, \"help\"");

	this->_is_server_connect = true;
	*/
}
/* ========================================================================= */
void SoftwareGSM::disconnect_server()
{
	this->A6_command(FF(F("AT+CIPSEND=5, \"close\"")), FF(F("OK")), FF(F("yy")), 10000, 2);
	this->A6_command(FF(F("AT+CIPCLOSE")), FF(F("OK")), FF(F("yy")), 5000, 2);
	this->_is_server_connect = false;
}
/* ========================================================================= */
void SoftwareGSM::send_answer(String &answer)
{
	// _reply = "AT+CIPSEND=";
	// _reply += answer.length();
	// _reply += ", \"" + answer + "\"";
	// AT+CIPSEND=2,""  -- 15 bytes
	//_reply = "";
	//_reply += answer.length();
	char* data = new char[15+answer.length()];

	strcpy(data, FF(F("AT+CIPSEND=")));
	strcat(data, String(answer.length()).c_str());
	strcat(data, FF(F(",\"")));
	strcat(data, answer.c_str());
	strcat(data, FF(F("\"")));

	//Serial.println(_serial_buf);
	//Serial.println(answer);
	//Serial.println(_reply);
	//Serial.println(data);
	Serial.print(F("Free RAM: "));
	Serial.println(memoryFree());
	//answer.
	this->A6_command(
		data, // _reply.c_str(),
		FF(F("OK")), FF(F("yy")), 10000, 1
	);
	delete [] data;
}
/* ========================================================================= */
void SoftwareGSM::send(String &command)
{
	if (command.equals(F("dsc")) && this->_is_server_connect) {
		this->disconnect_server(); return;
	}
	if (command.equals(F("cnct"))) {
		this->connect_to_server(FF(F("31.207.67.22")), FF(F("8082"))); return;
	}

	if (this->_is_server_connect) {
		this->send_answer(command);
	}
	else {
		this->_gsm_serial->println(command);
	}
}
/* ========================================================================= */
void SoftwareGSM::execute()
{
	Serial.flush();
	this->_gsm_serial->flush();
	// GSM MODULE SERIAL
	if (this->_gsm_serial->available())
	{
		while (this->_gsm_serial->available())
		{
			_serial_buf += char(this->_gsm_serial->read());
			delay(1);
		}
		this->prepare_buf();
		Serial.println(_serial_buf);
		viewFreeMemory();
		// this->_speaker->serial_answear();
	}
	// =======================================================================
	// SOFTWARE SERIAL
	if (Serial.available())
	{
		_serial_buf = "";
		while (Serial.available())
		{
			_serial_buf += char(Serial.read());
			//_serial_buf += Serial.readString();
			delay(1);
		}
		this->prepare_buf();
		Serial.println(_serial_buf);
		this->send(_serial_buf);
		// this->_speaker->serial_sending();
	}
}
/* ========================================================================= */
