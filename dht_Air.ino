#include <dht.h>                  //dht.zip 라이브러리를 설치
#define DHT22_PIN 7             //온도와 상대습도 센서 D7 연결

dht DHT;

float temperature ;
float humidity ;

void setup()
{
  Serial.begin(9600);             //시리얼모니터 출력
  delay(300);
}

void loop()
{
  float chk = DHT.read22(DHT22_PIN); 
  temperature = DHT.temperature;         //온도
  humidity = DHT.humidity;                //상대습도
  float DP = dewPoint(temperature, humidity);  //노점온도
  float AH =  ((6.112 * exp((17.67 * temperature) / (temperature + 245.5)) * humidity * 18.02) / ((273.15 + temperature) * 100 * 0.08314));   //절대습도
  float Psat =  (6.112 * exp((17.67 * temperature) / (temperature + 243.5))) / 10;  //포화수증기압 (단위 : kPa)
  float P =  (6.112 * exp((17.67 * temperature) / (temperature + 243.5)) * (humidity / 100)) / 10;  //수증기압 (단위 : kPa)
  float VPD = (Psat - P); //수증기압차 (단위 : kPa)

  //Serial.print("$");
  Serial.print(temperature, 1);           //온도
  Serial.println(" C");
  //Serial.print("/");
  Serial.print(humidity, 1);              //상대습도
  Serial.println(" %");
  //Serial.print("/");
  Serial.print(DP, 1);                   //노점온도
  Serial.println(" C");
  //Serial.print("/");
  Serial.print(AH, 2);                   //절대습도
  Serial.println(" kg/m3");
  //Serial.print("/");
  Serial.print(Psat, 2);                  //포화수증기압
  Serial.println(" kPa");
  //Serial.print("/");
  Serial.print(P, 2);                     //수증기압
  Serial.println(" kPa");
  //Serial.print("/");
  Serial.print(VPD, 2);                  //수증기압차
  Serial.println(" kPa");
  //Serial.println("$");
  delay(2000);
}

float dewPoint(float temperature, float humidity)
{
  // (1) Saturation Vapor Pressure = ESGG(T)
  float RATIO = 373.15 / (273.15 + temperature);
  float RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);

  // factor -3 is to adjust units - Vapor Pressure SVP * humidity
  float VP = pow(10, RHS - 3) * humidity;

  // (2) DEWPOINT = F(Vapor Pressure)
  float T = log(VP / 0.61078); // temp var
  return (241.88 * T) / (17.558 - T);
}
