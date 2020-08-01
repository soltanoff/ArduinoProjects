#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>

const byte rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte DHT11_PIN = 2;
DHT dht(DHT11_PIN, DHT11);

void setup() {
  dht.begin();

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  
  lcd.setCursor(0, 1);
  lcd.print("Humi:");
}

void loop() {
  float t = dht.readTemperature(false);
  float h = dht.readHumidity();
  
  if (isnan(h) || isnan(t)) { return; }

  lcd.setCursor(6, 0);
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(6, 1);
  lcd.print(h);
  lcd.print(" %");

  delay(500);
}