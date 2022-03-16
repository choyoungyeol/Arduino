#include <Sensirion.h>
#include <LiquidCrystal_I2C.h>
#define HeaterPin 7
#define Button 8

const uint8_t dataPin  =  2;
const uint8_t clockPin =  3;

float temperature;
float humidity;
float dewpoint;
int count = 0;
float set_Temp = 10;
float set_Temp_High = 13;

Sensirion tempSensor = Sensirion(dataPin, clockPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  pinMode(HeaterPin, OUTPUT);
  pinMode(Button, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Jeju Nat'l Univ.");
  lcd.setCursor(0, 1);
  lcd.print("Vegetables Lab.");
  Serial.begin(9600);
  delay(5000);
}

void loop()
{
  tempSensor.measure(&temperature, &humidity, &dewpoint);

  //  Serial.print("Temperature: ");
  //  Serial.print(temperature);
  //  Serial.print(" C, Humidity: ");
  //  Serial.print(humidity);
  //  Serial.print(" %, Dewpoint: ");
  //  Serial.print(dewpoint);
  //  Serial.println(" C");

  if (count == 3600) {
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp : ");
    lcd.print(temperature);
    lcd.print(" oC");
    lcd.setCursor(0, 1);
    lcd.print("Humi : ");
    lcd.print(humidity);
    lcd.print(" %");
    delay(20000);
    count = 0;
  } else {
    lcd.noBacklight();
    count = count + 1;
  }
  if (temperature >= set_Temp_High ) {
    digitalWrite(HeaterPin, LOW);
  }

  //  if ((temperature < set_Temp_High ) && (temperature >= set_Temp)) {
  //    digitalWrite(HeaterPin, LOW);
  //  }

  if (temperature < set_Temp ) {
    digitalWrite(HeaterPin, HIGH);
  }

  if (digitalRead(Button) == HIGH) {
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp : ");
    lcd.print(temperature);
    lcd.print(" oC");
    lcd.setCursor(0, 1);
    lcd.print("Humi : ");
    lcd.print(humidity);
    lcd.print(" %");
    delay(20000);
  }
  delay(1000);
}
