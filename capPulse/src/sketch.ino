/* 
 * Alternate voltage across an RC circuit:
 * Send from one pin, listen on another
 * Switch when voltage approaches saturation
 * Change LED level based on voltage
 * R = 1e5, C = 1e-1 F
*/
const int delayTime = 50;
const int outLed = 5;
//const int inSwitch = 12;
const int levelPin = A3;
const bool debug = true;
// digital output pin ids: HIGH/LOW (switchable)
commPins pins = {9,10,true};
// tolerances - when to switch?
int ledLow = 1;
int ledHigh = 99;
int ledTol = 0;
// initialize variables
int ledLevel = 0;
int probeLevel = 0;
#include "xian_helpers.h"
#include "commPins.h"

void setup()
{
    pinMode(outLed, OUTPUT);
    // pinMode(inSwitch, INPUT);
    pinMode(levelPin, INPUT);
    // set both to output, set voltage
    openPins(pins);
    Serial.begin(9600);
}


void loop()
{
    // read sensor and convert to PWM %level
    probeLevel = analogRead(levelPin);
    // reverse sense - high to low
    ledLevel = map(probeLevel, 1023, 0, 0, 100);
    // set led level accordingly
    analogWrite(outLed, ledLevel);
    if (debug) {
        // Print sensor reading to serial
        Serial << "Probe level: " << probeLevel << ", LED: " << ledLevel << ", pin state:" <<pins.state;
        Serial.println();
        delay(delayTime);
    }
    if ( 
        (ledLevel >= ledHigh + ledTol && !pins.state) ||
        (ledLevel <= ledLow - ledTol && pins.state)
    ){
        // need a delay here to ensure we don't
        // hop back into debounce right away
        switchPins(pins, debug);
        //delay(3*delayTime);
    }
}
