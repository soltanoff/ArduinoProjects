#include <Arduino.h>
#include <LiquidCrystal.h>

const byte rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte THER_PIN = 0;

int counter = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(0, 1);
  lcd.print("Time:");

  pinMode(THER_PIN, INPUT);
}

void processLCD() {
  lcd.setCursor(6, 1);
  counter++;
  if (counter == 10) { counter = 0; };
  lcd.print(counter);
}

void processThermister() {
  int data = analogRead(THER_PIN);
  double t = 4090 / (log((1025.0 * 10 / data - 10) / 10) + 4090 / 298.0) - 273.0;
  
  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.print(" C");
}

void loop() {
  delay(500);
  processLCD();
  processThermister();
}