#include <Adafruit_NeoPixel.h>
#include <RTClib.h>
#include <SoftwareSerial.h>
#define PIN        7
#define NUMPIXELS 16
#define DELAYVAL 500
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
RTC_DS3231 rtc;
SoftwareSerial Bluetooth(0, 1);
int Auto = 1;

void setup() {
  Serial.begin(9600);
  pixels.begin();
  Bluetooth.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();
  if (Auto == 1) {
    if ((now.hour() >= 9) && (now.hour() <= 9)) {
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 255));
        pixels.show();
        delay(DELAYVAL);
      }
    } else {
      pixels.clear();
      pixels.show();
    }
  }
  if (Auto == 0) {
    pixels.clear();
    pixels.show();
  }
  if (Bluetooth.available()) {
    char c = Bluetooth.read();
    if (c == 'a') {
      Auto = 1;
    }
    if (c == 'b') {
      Auto = 0;
    }
  }
  Auto = Auto;
  Serial.print(now.year());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.day());
  Serial.print(", ");
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.println();
  delay(3000);
}
