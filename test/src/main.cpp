#include "Arduino.h"
#include <SoftwareSerial.h>

#define SERIAL_PORT 9600
#define READ_DELAY 150

// BUFFER_SIZE 64 byte (this is max)
SoftwareSerial gsmSerial(10, 11); // RX, TX
String out;

void setup() {
    gsmSerial.begin(SERIAL_PORT);
    gsmSerial.println("AT+CMEE=2");
    Serial.begin(SERIAL_PORT);
    Serial.println("[READY]");
}

void remove(String& str, char symbol) {
    // str.trim();
    while (str.indexOf(symbol) >= 0)
        str.remove(str.indexOf(symbol), 1);
    str.replace("\n\n", " | ");
}

void cleaning(String& str) {
    // str.trim();
    remove(str, '\r');
    str.replace("\n\n", " | ");
    remove(str, '\n');
}

void softwareSerialInteract(SoftwareSerial& serial) {
    serial.listen();
    if (serial.available() > 0) {
        out = "";
        while (serial.available() > 0) {
            delay(READ_DELAY);
            out += (char) serial.read();
        }
        // remove(out, '\r');
        // remove(out, '\n');
        cleaning(out);
        out += " <---";
        Serial.println(out.c_str());
    }
}

void hardwareSerialInteract(SoftwareSerial& serial) {
    if (Serial.available() > 0) {
        serial.write(Serial.read());
    }
}

void loop() {
    softwareSerialInteract(gsmSerial);
    hardwareSerialInteract(gsmSerial);
} // void loop()
