/* code reads Decagon GS3 sensor output to the serial terminal.
WHITE wire: power supply/excitation, connected to 5v pin
RED wire: data line, connected to Arduino pin 2 (or another interrupt-capable pin)
bare wire: connected to GND
*/
 
#include <SDISerial.h>
 
 
#define INPUT_SIZE 30
#define NUMSAMPLES 5
#define DATA_PIN 4
#define INVERTED 1
 
int sensorDelay = 1000;
// bulk density used to calculate porewater conductivity (g/cm3)
float bulkDens = 0.4;  
// mineral density assumed to be 2.65 Mg/m3 (used 
// in porewater calculation from eq. 3 from GS-3 manual)
float theta = 1 - (bulkDens / 2.65); 
char* samples; 
 
 
SDISerial sdi_serial_connection(DATA_PIN, INVERTED);
 
 
void setup() {
  sdi_serial_connection.begin();
  Serial.begin(9600); 
  delay(3000);
}
 
 
void loop() {
 
  uint8_t i;
  // arrays to hold reps
  float dielectric[NUMSAMPLES];
  float soilMoist[NUMSAMPLES];
  float degC[NUMSAMPLES];
  float bulkEC[NUMSAMPLES];
  float porewaterEC[NUMSAMPLES];
  float solutionEC[NUMSAMPLES];
   
  // mean values
  float dielMean        = 0.0;
  float soilMoistMean   = 0.0;
  float degCMean        = 0.0;
  float bulkECMean      = 0.0;
  float porewaterECMean = 0.0;
  float solutionECMean  = 0.0;
 
  // take repeated samples
  for (i = 0; i < NUMSAMPLES; i++) {
    //char* response = get_measurement(); // get measurement data
    samples = get_measurement();
    while (strlen(samples) < 5) {
      samples = get_measurement();  
    }
  
    // first term is the sensor address (irrelevant to me)
    char* term1 = strtok(samples, "+");
     
    // second term is the dielectric conductivity & soil moisture
    term1      = strtok(NULL, "+");
    dielectric[i] = atof(term1);
               
    term1 = strtok(NULL, "+");
    degC[i] = atof(term1);
    term1 = strtok(NULL, "+");
    bulkEC[i] = atof(term1);
    // see eqs. 1 + 2 from GS3 manual (dS/m)
    porewaterEC[i] = ((80.3 - 0.37 * (degC[i] - 20)) * bulkEC[i] / 1000) / (dielectric[i] - 6);
   
   if (bulkEC[i] < 5) {
     soilMoist[i]  = (5.89 * pow(10.0, -6.0) * pow(dielectric[i], 3.0)) - (7.62 * pow(10.0, -4.0) * 
      pow(dielectric[i], 2.0)) + (3.67 * pow(10.0, -2.0) * dielectric[i]) - (7.53 * pow(10.0, -2.0));
   } else {
   soilMoist[i]  =  0.118 * sqrt(dielectric[i]) -0.117;
   }  
    // calculate EC of solution removed from a saturated soil paste, 
    // according to Decagon GS3 manual
    // see page 8 of GS3 manual (eq. 4)
    solutionEC[i] =  (bulkEC[i] / 1000 * soilMoist[i]) / theta; 
 
    // sum with each iteration
    dielMean        += dielectric[i];
    soilMoistMean   += soilMoist[i];
    degCMean        += degC[i];
    bulkECMean      += bulkEC[i];
    porewaterECMean += porewaterEC[i];
    solutionECMean  += solutionEC[i];
  }
   
  // Average readings for each parameter
  dielMean        /= NUMSAMPLES;
  soilMoistMean   /= NUMSAMPLES;
  degCMean        /= NUMSAMPLES;
  bulkECMean      /= NUMSAMPLES;
  porewaterECMean /= NUMSAMPLES;
  solutionECMean  /= NUMSAMPLES;
 
  Serial.print("dielectric: ");
  Serial.println(dielMean);
  Serial.print("VWC: ");
  Serial.println(soilMoistMean);
  Serial.print("bulk EC (uS/cm): ");
  Serial.println(bulkECMean);
  Serial.print("Degrees C: ");
  Serial.println(degCMean);
//  Serial.print("Solution EC (dS/m): ");
//  Serial.println(solutionECMean);
//  Serial.print("porewater EC (dS/m): "); 
//  Serial.println(porewaterECMean);
  delay(sensorDelay);
}
 
char* get_measurement(){
        // function by Joran Beasley: https://github.com/joranbeasley/SDISerial/blob/master/examples/SDISerialExample/SDISerialExample.ino
    char* service_request = sdi_serial_connection.sdi_query("?M!", sensorDelay);
    //you can use the time returned above to wait for the service_request_complete
    char* service_request_complete = sdi_serial_connection.wait_for_response(sensorDelay);
    // 1 second potential wait, but response is returned as soon as it's available
    return sdi_serial_connection.sdi_query("?D0!", sensorDelay);
}
