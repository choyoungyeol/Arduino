#include "DHT.h" //DHT 라이브러리 호출
#include <DigitShield.h> //DigitShield.h 라이브러리 호출
#define DHTPIN 12     // 온습도 센서가 12번에 연결
#define DHTTYPE DHT11   // DHT11 온습도 센서 사용
DHT dht(DHTPIN, DHTTYPE); //DHT 설정(12,DHT11)

int motor = 10; //모터 릴레이 핀
int water = 0 ; // water 변수 선언

void setup()
{
  Serial.begin(9600); //통신속도 9600으로 통신 시작
  DigitShield.begin();
  dht.begin();
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
}

void loop() {
  delay(500);
  float h = dht.readHumidity(); //습도값을 h에 저장
  float t = dht.readTemperature(); //온도값을 t에 저장
  float f = dht.readTemperature(true);// 화씨 온도를 측정합니다.
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print("Humidity: "); //문자열 출력
  Serial.print(h); //습도값 출력
  Serial.print("% ");
  DigitShield.setValue(h);
  delay(500);
  Serial.print("Temperature: ");
  Serial.print(hic); //온도값 출력
  Serial.println("C");
  DigitShield.setValue(t);
  delay(500);
  water = analogRead(A3);           //토양 습도 센서 아날로그핀 A3 번 사용 , A3 값 읽어와 water에 저장
  Serial.print("Soil humidity: ");  //토양 습도 체크
  Serial.println(water);
  DigitShield.setValue(water);

  if ( water > 400)   // 토양 습도 체크 800보다 낮으면 모터 동작 시켜 물공급 아니면 정지
  {
    digitalWrite(motor, HIGH);
    Serial.println("motor on");
  }
  else   {
    digitalWrite(motor, LOW);
    Serial.println("motor off");
  }
}
