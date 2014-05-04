/*
  Analog Input
 Demonstrates analog input by reading an analog sensor on analog pin 0 and
 turning on and off a light emitting diode(LED)  connected to digital pin 13. 
 The amount of time the LED will be on and off depends on
 the value obtained by analogRead(). 
 
 The circuit:
 * Potentiometer attached to analog input 0
 * center pin of the potentiometer to the analog pin
 * one side pin (either one) to ground
 * the other side pin to +5V
 * LED anode (long leg) attached to digital output 13
 * LED cathode (short leg) attached to ground
 
 * Note: because most Arduinos have a built-in LED attached 
 to pin 13 on the board, the LED is optional.
 
 
 Created by David Cuartielles
 modified 30 Aug 2011
 By Tom Igoe
 
 This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/AnalogInput
 
 */
#define NPULSE 50  // number measures per math
#define DELTAT 100 //millisec between measures
int pulse = 0; // print every...
char strBuff[100];
//
// define sensors
int sensorGreen = A0;    // select the input pin for green thermom
int sensorBlue = A1;    // select the input pin for blue thermom
double valGreen = 0;  // variable to store the value coming from the sensor
double valBlue = 0;  // variable to store the value coming from the sensor
// arrays to store readings
double vecGreen[NPULSE] = {0};
double vecBlue[NPULSE] = {0};
/*
card related
*/
#include <SD.h>
// for seeeduino v3.1
//{ 
//  Serial.println("Trouble initializing card.");
//}
//const char filename[] = "temp02.txt";
const int chipSelect = 10;
  // can't use chipselect pin for input
//pinMode(10, OUTPUT);
int sdinit =   SD.begin(chipSelect);  
File dataFile = SD.open("TEMP04.CSV", FILE_WRITE);


/* 
processing functions
*/
double mkTemp( double sensor ) {
  // from https://www.sparkfun.com/products/10988
  return ((sensor * 0.004882)-0.50)*100;
}

void doSample(int pin, int counter, double &val, double *vals) {
    int reading = mkTemp(analogRead(pin));
    val += reading;
    vals[counter] = reading;
}

void doMath(int ncount, double &val, double *vals) {
  // ncount = length of &vals
  // compute mean and sd, store sd in vals[0]
  double sd = 0;
  // mean 
  val /= ncount;
  for (int ii=0; ii<ncount; ii++){
    // sum of squared difference
    sd += pow(vals[ii]-val, 2);
  };
  sd /= ncount;
  sd = sqrt(sd);
  // place in vals[0]
  vals[0] = sd;
}

void doConvert(double num, char *retBuff) {
  // buffer for conversion
  char tempBuff[16];
  // convert to string
  // from http://forum.arduino.cc/index.php?topic=125946.0
  dtostrf(num, 5, 2, tempBuff);
  // place on return buffer
  strcat( retBuff, tempBuff);
};

void doPrint(char *color, char *buff, double mean, double sd){
  // add color to buffer
  strcat(buff, color);
  strcat(buff, ",");
  // number of minutes since start
  char nsec[10];
  itoa(millis() / (1000), nsec, 10);
  strcat(buff, nsec);
  strcat(buff, ",");
  // convert mean and sd to strings, add to buffer
  doConvert(mean, buff);
  strcat(buff, ",");
  doConvert(sd, buff);
  strcat(buff, "\n");
  //strcat(buff, ") ");
};

void setup() {
  // declare the ledPin as an OUTPUT:
  //pinMode(ledPin, OUTPUT);
//  Serial.begin(9600);
  //if (!dataFile) {
    //Serial.println("Can't open file");
  //} else { 
    //Serial.println("File opened.");
  //}
}

void loop() {
  // reset:
  // clear output character buffer
  memset(&strBuff[0], 0, sizeof(strBuff));
  // dont need to clear value buffers, just be safe...
  memset(&vecGreen[0], 0, sizeof(vecGreen));
  memset(&vecBlue[0], 0, sizeof(vecBlue));
  // remove mean from values
  valGreen = 0;
  valBlue = 0;
  pulse = 0;
  while (pulse < NPULSE) {
    doSample(sensorGreen, pulse, valGreen, vecGreen); 
    doSample(sensorBlue, pulse, valBlue, vecBlue); 
    pulse++; 
    delay(DELTAT);
  }
  doMath(NPULSE, valGreen, vecGreen);
  doMath(NPULSE, valBlue, vecBlue);
  // append mean /sd to the char buffer
  doPrint("Green", strBuff, valGreen, vecGreen[0]);
  doPrint("Blue", strBuff, valBlue, vecBlue[0]);

  // turn the ledPin on
  //digitalWrite(ledPin, HIGH);          
  // turn the ledPin off:        
  //digitalWrite(ledPin, LOW);   
  // stop the program for for <sensorValue> milliseconds: 
  int bytes = dataFile.write(strBuff);
  dataFile.flush();
  //Serial.println(bytes);
  //Serial.println(strBuff);
}
