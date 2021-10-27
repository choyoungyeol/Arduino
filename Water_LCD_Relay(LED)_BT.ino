#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<SoftwareSerial.h>
#define Water_Pin A0
#define Water_OFF 8
#define Water_ON 9

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial Bluetooth(0, 1);

int Auto = 1;

String readString;

void setup() {
  Serial.begin(9600);
  pinMode(Water_OFF, OUTPUT);
  pinMode(Water_ON, OUTPUT);
  Bluetooth.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(3, 1);
  lcd.print("Hi, JNU!");
  delay(5000);
}

void loop() {

  int Water = analogRead(Water_Pin);
  int Water_Content = map(Water, 589, 291, 0, 100);

  readString = "";

  while (Bluetooth.available()) {
    delay(3);
    char c = Bluetooth.read();
    readString += c;
  }

  if (Water_Content >= 100) {
    Water_Content = 100;
  }

  if (Water_Content <= 0) {
    Water_Content = 0;
  }

  if (Auto == 1) {
    if (Water_Content <= 20) {
      digitalWrite(Water_ON, HIGH);
      digitalWrite(Water_OFF, LOW);
    } else {
      digitalWrite(Water_ON, LOW);
      digitalWrite(Water_OFF, HIGH);
    }
  } 
  
  if (readString.length() > 0) {
    if (readString == "x") {
      Auto = 1;
    }
    if (readString == "y") {
      Auto = 0;
    }

    if (readString == "a") {
      digitalWrite(Water_ON, HIGH);
      digitalWrite(Water_OFF, LOW);
    }

    if (readString == "b") {
      digitalWrite(Water_ON, LOW);
      digitalWrite(Water_OFF, HIGH);
    }
  }
  Auto = Auto;
  String data = String(Water) + "," + String(Water_Content) + "," + String(Auto);
  Serial.println(data);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water = ");
  lcd.print(Water);
  lcd.setCursor(1, 1);
  lcd.print("W C = ");
  lcd.print(Water_Content);
  lcd.print(" %");
  delay(5000);
}
