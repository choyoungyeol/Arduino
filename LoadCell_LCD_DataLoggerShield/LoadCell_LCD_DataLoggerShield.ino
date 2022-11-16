#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SD.h>
#include <RTClib.h>
#include <SPI.h>

#define calibration_factor -39250.0
#define DOUT  3
#define CLK  2
HX711 scale(DOUT, CLK);

LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int CS_PIN      = 10; //SS for SD Shield
const int SD_POW_PIN  = 8; //Power for SD Shield
const int RTC_POW_PIN = A3; //Used as digital output
const int RTC_GND_PIN = A2; //Used as digital output

int refresh_rate = 1000;

RTC_Millis RTC;

int time_check = 0;

void setup() {
  Serial.begin(9600);
  scale.set_scale(calibration_factor);
  scale.tare();

  pinMode(CS_PIN,   OUTPUT);
  pinMode(SD_POW_PIN, OUTPUT);
  pinMode(RTC_POW_PIN, OUTPUT);
  pinMode(RTC_GND_PIN, OUTPUT);

  //Setup power and ground pins for both modules
  digitalWrite(SD_POW_PIN, HIGH);
  digitalWrite(RTC_POW_PIN, HIGH);
  digitalWrite(RTC_GND_PIN, LOW);

  RTC.begin(DateTime(F(__DATE__), F(__TIME__)));

  //Initialize SD card
  if (!SD.begin(CS_PIN))
  {
    Serial.println(F("Card Failure"));
    return;
  }
  Serial.println(F("Card Ready"));

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Jeju Nat'l Univ.");
  lcd.setCursor(0, 1);
  lcd.print("Vegetables Lab.");
  delay(5000);
  DateTime now = RTC.now();
  time_check = now.minute();
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

  DateTime now = RTC.now();

  int time_time = now.minute();
  //Open a file and write to it.

  if (time_time != time_check) {
    File dataFile = SD.open("log.csv", FILE_WRITE);
    if (dataFile)
    {
      dataFile.print(now.year());
      dataFile.print("-");
      dataFile.print(now.month());
      dataFile.print("-");
      dataFile.print(now.day());
      dataFile.print(" ");
      dataFile.print(now.hour());
      dataFile.print(":");
      dataFile.print(now.minute());
      dataFile.print(":");
      dataFile.print(now.second());
      dataFile.print(",");
      dataFile.print(Weight_lbs, 2); //scale.get_units() returns a float
      dataFile.print(","); //You can change this to kg but you'll need to refactor the calibration_factor
      dataFile.print(Weight_kg, 3); //scale.get_units() returns a float
      dataFile.println("");
      dataFile.close(); //Data isn't actually written until we close the connection!
      //Print same thing to the screen for debugging
      time_check = time_time;
    }
  }

  if ((now.hour() > 18) || (now.hour() < 12)) {
    lcd.noBacklight();
  } else {
    lcd.backlight();
  }

  delay(refresh_rate);
}
