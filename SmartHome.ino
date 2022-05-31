#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define dhtPin 8
#define dhtType DHT11
#define Fan 11
#define Light 6
#define NUMPIXELS 3
#define DELAYVAL 500

DHT dht(dhtPin, dhtType);
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial BT(0, 1);
Servo myservo;
Adafruit_NeoPixel pixels(NUMPIXELS, Light, NEO_GRB + NEO_KHZ800);

String readString;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pixels.begin();
  lcd.init();
  lcd.backlight();
  //lcd.noBacklight();
  lcd.setCursor(0, 0);
  lcd.print("JNU");
  lcd.setCursor(0, 1);
  lcd.print("Hello");

  BT.begin(9600);
  pinMode(Fan, OUTPUT);
  myservo.attach(13);
}

void loop() {
  // put your main code here, to run repeatedly:
  int temp = dht.readTemperature();
  int humi = dht.readHumidity();
  //
  //  Serial.print(temp);
  //  Serial.print(" oC, ");
  //  Serial.print(humi);
  //  Serial.println(" %");
  //  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  lcd.print(temp);
  lcd.print(" oC");
  lcd.setCursor(0, 1);
  lcd.print("Humi = ");
  lcd.print(humi);
  lcd.print(" %");
  delay(2000);

  while (BT.available()) {
    delay(3);
    char c = BT.read();
    readString += c;
  }
  if (readString.length() > 0) {
    if (readString == "a") {
      digitalWrite(Fan, HIGH);
    }
    if (readString == "b") {
      digitalWrite(Fan, LOW);
    }
    if (readString == "c") {
      myservo.write(90);
    }
    if (readString == "d") {
      myservo.write(180);
    }
    if (readString == "e") {
      pixels.clear();
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 255, 255));
        pixels.show();
        delay(DELAYVAL);
      }
    }
    if (readString == "f") {
      pixels.clear();
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
        delay(DELAYVAL);
      }
    }
  }
  readString = "";
  String data = String(temp) + ", " + String(humi) + ",";
  Serial.println(data);
}
