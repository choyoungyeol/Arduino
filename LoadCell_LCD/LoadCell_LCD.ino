#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define calibration_factor -39060.0
#define DOUT  3
#define CLK  2
HX711 scale(DOUT, CLK);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  Serial.begin(9600);
  scale.set_scale(calibration_factor);
  scale.tare();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Jeju Nat'l Univ.");
  lcd.setCursor(0, 1);
  lcd.print("Vegetables Lab.");
  delay(5000);
}

void loop() {
  float Weight_lbs = scale.get_units();
  float Weight_kg = Weight_lbs * 0.453592;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WT = ");
  lcd.print(Weight_lbs, 2);
  lcd.print(" lbs");
  lcd.setCursor(0, 1);
  lcd.print("WT = ");
  lcd.print(Weight_kg, 3);
  lcd.print(" kg");
  delay(5000);
}
