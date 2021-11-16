#include <SPI.h>
#include <LoRa.h>   //Download here: http://electronoobs.com/eng_arduino_LoRa_SX1278.php.php
String inString = "";    // string to hold input
String val = "";

void setup() {
  Serial.begin(9600);

  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(868E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {

  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // read packet
    while (LoRa.available())
    {
      int inChar = LoRa.read();
      inString += (char)inChar;
      val = inString.toInt();
    }
    inString = "";
    LoRa.packetRssi();
  }

  Serial.println(val);
  delay(5000);
}
