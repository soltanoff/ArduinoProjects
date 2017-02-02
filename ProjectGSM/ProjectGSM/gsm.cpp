/* ========================================================================= */
#include "gsm.h"
/* ========================================================================= */
SoftwareGSM::SoftwareGSM(short rx, short tx, long serial_port)
{
	this->_is_server_connect = false;
	// this->_rx_pin = rx;
	// this->_tx_pin = tx;
	// this->_serial_port = serial_port;

	// this->_gsm_serial = new SoftwareSerial(_rx_pin, _tx_pin);
	// this->_gsm_serial->begin(this->_serial_port);  // Скорость порта для связи Arduino с GSM модулем
	
	this->_gsm_serial = new SoftwareSerial(rx, tx);
	this->_gsm_serial->begin(serial_port);  // Скорость порта для связи Arduino с GSM модулем

	delay(100);
	this->_gsm_serial->println("AT+IPR=" + String(serial_port));  // устанавливаем скорость шилда
	delay(100);
	
	this->_speaker = new SoftwareSpeaker();
	this->_speaker->module_initional();
	delay(1000);

	for (short i = 0; i < 5; i++)
	{
		this->_gsm_serial->println("AT");
		delay(800);
	}
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
	this->_gsm_serial->println("AT+CMGF=1");
	delay(2000);

	this->_gsm_serial->print("AT+CMGS=\"");
	this->_gsm_serial->print(phone_number);
	this->_gsm_serial->write(0x22);
	this->_gsm_serial->write(0x0D);	// hex код возврата коректки 
	this->_gsm_serial->write(0x0A);	// hex код новой строки

	// delay(2000);
	this->_gsm_serial->print(text);
	delay(500);

	this->_gsm_serial->println(char(26));	// ASCII код Сtrl+Z
	delay(1000);

	// Serial.println("AT+CMGF=0");
	this->_speaker->sms_sending();
}
/* ========================================================================= */
void SoftwareGSM::call_number(const char *phone_number)
{
	this->_gsm_serial->print("ATD");
	this->_gsm_serial->println(phone_number);
	// Serial.println(";");
	delay(10000);
	this->_gsm_serial->println("ATH");
}
/* ========================================================================= */
void SoftwareGSM::prepare_command()
{
	_serial_buf += '_';
	_serial_buf.remove(_serial_buf.length());  // убираем коретку
	_serial_buf.remove(_serial_buf.length() - 1);  // убираем коретку
	_serial_buf.remove(_serial_buf.length() - 2);  // убираем коретку
}
/* ========================================================================= */
void SoftwareGSM::prepare_answer(const char* command)
{
	// удаляем с ответа саму команду и служебные символы
	if (_serial_buf.indexOf(command) > -1)
		_serial_buf.remove(0, strlen(command) + 4); 
	this->prepare_command();
}
/* ========================================================================= */
bool SoftwareGSM::wait_answer(const char* command)
{
	_serial_buf = "";
	this->_gsm_serial->println(command);
	Serial.println(command);
	this->_speaker->serial_sending();

	while (true)
	{
		if (this->_gsm_serial->available())
		{
			while (this->_gsm_serial->available())
			{
				_serial_buf += char(this->_gsm_serial->read());
				delay(10);
			}
			this->_speaker->serial_answear();
			this->prepare_answer(command);
			return true;
		}
	}
}
/* ========================================================================= */
bool SoftwareGSM::wait_ok_status(const char* command)
{
	this->wait_answer(command);
	Serial.println(_serial_buf);
	if (_serial_buf.equals("OK"))
		return true;
	return false;
}
/* ========================================================================= */
void SoftwareGSM::connect_to_server(const char* ip, const char* port)
{
	Serial.println("Connect to server...");
	
	this->wait_ok_status("AT+CGATT?");
	delay(2000);
	// Прикрепиться сети если 1, 
	// открепиться если 0 (длительность: 8 сек)
	if (_serial_buf.indexOf("+CGATT:0") > -1)
	{
		this->wait_answer("AT+CGATT=1");  // _gsm_serial->println("AT+CGATT=1");
		Serial.println(_serial_buf);
		delay(3000);
	}
	// Задаем контекст поключения PDP (Packet Data Protocol)
	// 1 - индентификатор контекста PDP (max 7)
	// "IP" - тип протокола (PDP type: IP, IPV6, PPP Point to Point Protocol)
	// "cmnet" - имя точки доступа
	this->wait_ok_status("AT+CGDCONT=1,\"IP\",\"cmnet\"");
	delay(3000);
	// Активируем заданный контекст (длительность: 3-4 сек)
	// 1 - состояние (вкл/выкл)
	// 1 - индентификатор контекста PDP
	this->wait_ok_status("AT+CGACT=1,1");
	delay(5000);
	// Начать TCP/UDP подключение 
	// (длительность: 2-3 сек)
	_serial_buf = "AT+CIPSTART=\"TCP\",\"";
	_serial_buf += ip;
	_serial_buf += "\", ";
	_serial_buf += port;
	this->_gsm_serial->println(_serial_buf.c_str());
	delay(5000);

	wait_ok_status("AT+CIPSEND=4, \"help\"");
	this->_is_server_connect = true;
	delay(1000);
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
	this->wait_ok_status("AT+CIPCLOSE");
	this->_is_server_connect = false;
}
/* ========================================================================= */
void SoftwareGSM::send(String &command)
{
	if (command.equals("dsc") && this->_is_server_connect)
	{
		this->disconnect_server(); return;
	}
	if (command.equals("cnct"))
	{
		this->connect_to_server("31.207.65.87", "8082"); return;
	}

	if (this->_is_server_connect)
	{
		this->_gsm_serial->println(
			"AT+CIPSEND=" + String(command.length()) + ", \"" + command + "\""
		);
	}
	else
	{
		this->_gsm_serial->println(command);
	}
}
/* ========================================================================= */
void SoftwareGSM::execute()
{
	// GSM MODULE SERIAL
	if (this->_gsm_serial->available())
	{
		while (this->_gsm_serial->available())
		{
			_serial_buf += char(this->_gsm_serial->read());
			delay(10);
		}
		Serial.println(_serial_buf);
		this->_speaker->serial_answear();
	}
	_serial_buf = "";
	// SOFTWARE SERIAL
	if (Serial.available())
	{
		while (Serial.available())
		{
			_serial_buf += char(Serial.read());
			delay(10);
		}
		this->prepare_command();
		this->send(_serial_buf);
		this->_speaker->serial_sending();
	}
	_serial_buf = "";
}
/* ========================================================================= */
