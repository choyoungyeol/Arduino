//시리얼 모니터를 통해 LED 제어하기
#define LED_Pin 7

void setup() {
  Serial.begin(9600);
  pinMode(LED_Pin, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'a') {
      digitalWrite(LED_Pin, HIGH);
    }
    if (c == 'b') {
      digitalWrite(LED_Pin, LOW);
    }
  }
}
