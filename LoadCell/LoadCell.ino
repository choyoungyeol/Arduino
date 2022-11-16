#include "HX711.h"
#define calibration_factor -39060.0 
#define DOUT  3
#define CLK  2
HX711 scale(DOUT, CLK);

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 scale demo");
  scale.set_scale(calibration_factor); 
  scale.tare(); 
  Serial.println("Readings:");
}

void loop() {
  float Weight_lbs = scale.get_units();
  float Weight_kg = Weight_lbs * 0.453592;
  Serial.print("Reading: ");
  Serial.print(Weight_lbs, 2); 
  Serial.print(" lbs"); 
  Serial.println();
  Serial.print(Weight_kg, 3); 
  Serial.print(" kg"); 
  Serial.println();
  delay(2000);

}
