#include "xian_helpers.h"
#include "toneNotes.h"
const int debounceTime = 50;
// play or not? switch
const int inSwitch = 12;
// read for pitch
const int levelPin = A5;
// piezo
const int outPin = 3;
bool playOn = false;
int playPitch;
struct FreqRange {
    int low;
    int high;
};
FreqRange freqrange = {100, 5e3};

void setup()
{
    //Serial.begin(9600);
}

void loop()
{
    // read sensor and convert to Freq:
    playPitch = analogRead(levelPin);
    playPitch = map(playPitch, 0, 1023, freqrange.low, freqrange.high);
    if (debounceBool(inSwitch, debounceTime)){
        // invert on button
        playOn = !playOn;
        // pause so we don't debounce right away
        delay(4*debounceTime);
    }
    if (playOn) {
        tone(outPin, playPitch);
    } else {
        noTone(outPin);
    }
}
