#include <LoRa.h>
#include <Sensirion.h>
#include <LiquidCrystal_I2C.h>

const uint8_t dataPin  =  5;
const uint8_t clockPin =  6;

float temperature;
float humidity;
float dewpoint;

String readString;

Sensirion tempSensor = Sensirion(dataPin, clockPin);
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  Serial.begin(115200);

  while (!Serial);
  Serial.println("LoRa Sender");
  if (!LoRa.begin(915E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  lcd.init();
  lcd.backlight();
}

void loop()
{

  tempSensor.measure(&temperature, &humidity, &dewpoint);

  float AH =  ((6.112 * exp((17.67 * temperature) / (temperature + 245.5)) * humidity * 18.02) / ((273.15 + temperature) * 100 * 0.08314));
  float Psat =  (6.112 * exp((17.67 * temperature) / (temperature + 243.5))) / 10;
  float P =  (6.112 * exp((17.67 * temperature) / (temperature + 243.5)) * (humidity / 100)) / 10;
  float VPD = (Psat - P);

  lcd.clear();
  lcd.setCursor(0, 0); // set the cursor to column 0, line 0
  lcd.print("Temp : ");
  lcd.print(temperature);
  lcd.print(" oC");
  lcd.setCursor(0, 1); // set the cursor to column 0, line 1
  lcd.print("Humi : ");
  lcd.print(humidity);
  lcd.print(" %");
  lcd.setCursor(0, 2); // set the cursor to column 0, line 0
  lcd.print("VPD  : ");
  lcd.print(VPD);
  lcd.print(" kPa");
  lcd.setCursor(0, 3); // set the cursor to column 0, line 1
  lcd.print("A H  : ");
  lcd.print(AH);
  lcd.print(" g/m3");
  delay(3000);

  String data = "{\"Temperature\":" + String(temperature) + ",\"Humidity\":" + String(humidity) + ",\"Dew_Temperature\":" + String(dewpoint) + ",\"Absolute_Humidity\":" + String(AH) + ",\"Vapor_pressure\":" + String(P) + ",\"VPD\":" + String(VPD) +  "}";
  Serial.println(data);
  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();
  delay(5000);
}
