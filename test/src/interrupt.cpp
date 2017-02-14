#include <SoftwareSerial.h>

volatile SoftwareSerial gsm(2, 11); // RX, TX

volatile String buf;

void setup() {
  buf = "";
  Serial.begin(9600);
  Serial.println("Goodnight moon!");

  gsm.begin(9600);
  gsm.println("AT");

  attachInterrupt(digitalPinToInterrupt(2), test, CHANGE);
}

void loop() {
  // if (gsm.available()) {
  //   Serial.write(gsm.read());
  // }
  if (Serial.available()) {
    gsm.write(Serial.read());
  }
}

void test() {
  if (gsm.available()) 
    // Serial.write(gsm.read());
    buf += (char) gsm.read();
  Serial.print("Interrupt! ");
  Serial.println(buf.c_str());
}

