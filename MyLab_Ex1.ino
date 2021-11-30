#include <Sensirion.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const uint8_t dataPin  =  2;
const uint8_t clockPin =  3;

float temperature;
float humidity;
float dewpoint;

Sensirion tempSensor = Sensirion(dataPin, clockPin);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

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
}
