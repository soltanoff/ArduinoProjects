#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(10, 11); // RX, TX
const char PHONE_NUMBER[]="8хххххххххх";
const int SERIAL_PORT = 115200;


void send_sms(){
	delay(300); 
	Serial.begin(SERIAL_PORT);
	delay(300); 

	Serial.println("AT+CMGF=1");    
	delay(2000);
	Serial.print("AT+CMGS=\"");
	
	Serial.print(PHONE_NUMBER); 
	Serial.write(0x22);
	Serial.write(0x0D);  // hex код возврата коректки 
	Serial.write(0x0A);  // hex код новой строки
	
	delay(2000);
	Serial.print("GSM A6 test message!");
	delay(500);
	Serial.println (char(26));	// ASCII код Сtrl+Z
}

void setup() {
	digitalWrite(4, HIGH);	// Питание модуля
  
	Serial.begin(SERIAL_PORT);  // Скорость порта для связи Arduino с компьютером
	Serial.println("Start programm!");
	
	gsmSerial.begin(SERIAL_PORT);  // Скорость порта для связи Arduino с GSM модулем
	delay(9000);
	gsmSerial.println("AT");
}

void loop() {
	if (gsmSerial.available())
		Serial.write(gsmSerial.read());
	if (Serial.available())
		gsmSerial.write(Serial.read());
}
