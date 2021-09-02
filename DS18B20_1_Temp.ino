#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void)
{
   Serial.begin(9600); 
   Serial.println("Arduino Digital Temperature"); 
   sensors.begin();
}

void loop(void)
{ 
   sensors.requestTemperatures(); 
   Serial.print("Temperature is: ");
   Serial.println(sensors.getTempCByIndex(0)); 
   delay(1000);
}
