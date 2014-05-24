const int debounceTime = 50;
const int outLed = 5;
const int inSwitch = 12;
const int levelPin = A4;
const bool debug = false;
// digital output pin ids: HIGH/LOW (switchable)
commPins pins = {0,1};
int ledLevel = 0;
int probeLevel = 0;

void setup()
{
    pinMode(outLed, OUTPUT);
    pinMode(inSwitch, INPUT);
    pinMode(levelPin, INPUT);
    // set both to output, set voltage
    openPins(pins);
    Serial.begin(9600);
}

#include "xian_helpers.h"
#include "commPins.h"

void loop()
{
    // read sensor and convert to PWM %level
    probeLevel = analogRead(levelPin);
    ledLevel = map(probeLevel, 0, 1023, 0, 100);
    // set led level accordingly
    analogWrite(outLed, ledLevel);
    // Print sensor reading to serial
    //Serial.println(probeLevel);
    if (debug) {
        Serial << probeLevel << ", " << ledLevel;
        Serial.println();
    }
    // switch hi/low sense on signal
    if (debounceBool(inSwitch, debounceTime, debug)){
        switchPins(pins, debug);
        // need a delay here to ensure we don't
        // hop back into debounce right away
        delay(4*debounceTime);
    }
}
