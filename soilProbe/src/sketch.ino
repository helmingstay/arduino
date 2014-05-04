#include "helpers.h"
#define LED_PIN 13
const int delayTime = 1e3;
const int outLed = 5;
const int inSwitch = 12;
const int levelPin = A4;
// Rx/Tx digital pins
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

void loop()
{
    //lineRead = analogRead(A0);
    // read pot and convert to TDW %level
    probeLevel = analogRead(levelPin);
    //Serial.println(probeLevel);
    ledLevel = map(probeLevel, 0, 1023, 0, 100);
    Serial << probeLevel << ", " << ledLevel;
    Serial.println();
    analogWrite(outLed, ledLevel);
    //int val = ;
    if (digitalRead(inSwitch) != LOW) { 
        //digitalWrite(outLed, HIGH);
        //analogWrite(outLed, ledLevel);
        switchPins(pins);
        delay(delayTime);
    } else {
        //digitalWrite(outLed, LOW);
        //analogWrite(outLed,0);
        delay(delayTime);
    }
    /*
        delay(500);
        digitalWrite(outLed, LOW);
        delay(5000);
    */
}
