// Rx/Tx digital pins
struct commPins {
    int high;
    int low;
    bool state;
};

// set voltage to high & low, resp
// maintainence function, don't call this....
void setPins( const commPins pins ) {
    digitalWrite(pins.high, HIGH);
    digitalWrite(pins.low, LOW);
}

//initial setup
void openPins( const commPins pins ) {
    // set both pins to output
    pinMode(pins.high, OUTPUT);
    pinMode(pins.low, OUTPUT);
    setPins(pins);
}
void switchPins( commPins &pins, const bool debug=false) {
    // switch hi/low sense
    int tmpPin = pins.high;
    pins.high = pins.low;
    pins.low = tmpPin;
    // configuration id
    pins.state = !pins.state;
    // update voltage
    setPins(pins);
    if (debug) {
        Serial << "High=" << pins.high << ", Low=" << pins.low;
        Serial.println();
    }
}



// like above, but one pin is input
// careful, must use R between pins
// set voltage to high & input, resp
// maintainence function, don't call this....
void setPinsRead( const commPins pins ) {
    digitalWrite(pins.high, HIGH);
    //digitalWrite(pins.low, LOW);
}

//initial setup
void openPinsRead( const commPins pins ) {
    // set high pin to output, low pin to input
    pinMode(pins.high, OUTPUT);
    pinMode(pins.low, INPUT);
    setPins(pins);
}
void switchPinsRead( commPins &pins, const bool debug=false) {
    // switch hi/low sense
    int tmpPin = pins.high;
    pins.high = pins.low;
    pins.low = tmpPin;
    // configuration id
    pins.state = !pins.state;
    // update voltage
    setPinsRead(pins);
    if (debug) {
        Serial << "High=" << pins.high << ", Low=" << pins.low;
        Serial.println();
    }
}
