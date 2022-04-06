#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define ONE_WIRE_BUS 2
#define Pin 6

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

uint8_t sensor1[8] = { 0x28, 0xFF, 0x6E, 0x73, 0x71, 0x17, 0x04, 0x7C };
uint8_t sensor2[8] = { 0x28, 0xFF, 0x2B, 0xFB, 0x71, 0x17, 0x04, 0x82 };
float Dry_Temp;
float Wet_Temp;

void setup(void) {
  pinMode(Pin, INPUT);
  Serial.begin(9600);
  sensors.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Jeju Nat'l Univ.");
  lcd.setCursor(1, 1);
  lcd.print("Hi, Vegetables!");
  delay(5000);
}

void loop(void) {
  float Patm = 101.325; //기압 kPa
  sensors.requestTemperatures();
  Wet_Temp = sensors.getTempC(sensor1); //습구온도
  Dry_Temp = sensors.getTempC(sensor2); //건구온도
  float Psdt = 0.61078 * exp((17.27 * Dry_Temp) / (237.3 + Dry_Temp)); //kPa
  float Pswt = 0.61078 * exp((17.27 * Wet_Temp) / (237.3 + Wet_Temp)); //kPa
  float Pv = Pswt - Patm * 0.000662 * (Dry_Temp - Wet_Temp); //수증기압
  float Humidity = 100 * Pv / Psdt; //상대습도
  float VPD = Psdt * (1 - Humidity / 100); //수증기압포차
  float Dew_Temp = (Dry_Temp - (100 - Humidity) / 5); //노점온도
  float AH = 2.16679 * Pv / (273.15 + Dry_Temp); //절대습도
  Serial.print("Dry Temp : "); Serial.println(Dry_Temp);
  Serial.print("Wet Temp: "); Serial.println(Wet_Temp);
  Serial.print("Dew Temp : "); Serial.println(Dew_Temp);
  Serial.print("Humidity : "); Serial.println(Humidity);
  Serial.print("AH : "); Serial.println(AH);
  Serial.print("SVP : "); Serial.println(Psdt);
  Serial.print("Pv : "); Serial.println(Pv);
  Serial.print("VPD : "); Serial.println(VPD);

  int switchwalue = digitalRead(Pin);
  if (switchwalue == LOW) {
    lcd.noBacklight();
  } else {
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dry_T: ");
    lcd.print(Dry_Temp);
    lcd.print(" oC");
    lcd.setCursor(0, 1);
    lcd.print("Wet_T: ");
    lcd.print(Wet_Temp);
    lcd.print(" oC");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dew_T: ");
    lcd.print(Dew_Temp);
    lcd.print(" oC");
    lcd.setCursor(0, 1);
    lcd.print("R   H: ");
    lcd.print(Humidity);
    lcd.print(" %");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("A H: ");
    lcd.print(AH);
    lcd.print(" g/m3");
    lcd.setCursor(0, 1);
    lcd.print("SVP: ");
    lcd.print(Psdt);
    lcd.print(" kPa");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("P v: ");
    lcd.print(Pv);
    lcd.print(" kPa");
    lcd.setCursor(0, 1);
    lcd.print("VPD: ");
    lcd.print(VPD);
    lcd.print(" kPa");
    delay(2000);
  }
}
