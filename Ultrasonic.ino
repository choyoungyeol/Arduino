#define echo 8
#define trig 9

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  float cycletime;
  float distance;
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  cycletime = pulseIn(echo, HIGH);
  distance = ((340 * cycletime) / 10000) / 2;
  Serial.print("Distance:");
  Serial.print(distance);
  Serial.println("cm");
  delay(500);
}
