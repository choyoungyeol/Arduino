#include <Sensirion.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint8_t dataPin  =  2;
const uint8_t clockPin =  3;

float temperature;
float humidity;
float dewpoint;

Sensirion tempSensor = Sensirion(dataPin, clockPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("JEJU Nat'l Univ.");
  lcd.setCursor(0, 1);
  lcd.print("Vegetables Info.");
  delay(5000);
}

void loop()
{
  tempSensor.measure(&temperature, &humidity, &dewpoint);

  for (int i = 0; i < 10; i++) { //평균온도
    temperature += temperature;
    delay(10);
  }
  temperature /= 1000;

  for (int i = 0; i < 10; i++) { //평균상대습도
    humidity += humidity;
    delay(10);
  }
  humidity /= 1000;

  int index = 1.8 * temperature - 0.55 * (1 - humidity / 100) * (1.8 * temperature - 26) + 32;

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Dewpoint: ");
  Serial.print(dewpoint);
  Serial.println(" C");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  lcd.print(temperature);
  lcd.print(" 'C");
  lcd.setCursor(0, 1);
  lcd.print("Humi = ");
  lcd.print(humidity);
  lcd.print(" %");

  delay(5000);

  switch (index) {
    case 1 ... 67:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Index = ");
      lcd.print(index);
      lcd.setCursor(0, 1);
      lcd.print("Index = Great");
      break;
    case 68 ... 74 :
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Index = ");
      lcd.print(index);
      lcd.setCursor(0, 1);
      lcd.print("Index = Good");
      break;
    case 75 ... 79 :
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Index = ");
      lcd.print(index);
      lcd.setCursor(0, 1);
      lcd.print("Index = Soso");
      break;
    case 80 ... 100 :
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Index = ");
      lcd.print(index);
      lcd.setCursor(0, 1);
      lcd.print("Index = Bad");
      break;
  }
  delay(5000);
}
