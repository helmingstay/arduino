// Insertion style streaming to Serial
template<class T> inline Print &operator <<(Print &obj, T arg) { 
    obj.print(arg); return obj; 
} 
// Rx/Tx digital pins
struct commPins {
    int high;
    int low;
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
void switchPins( commPins &pins ) {
    // switch hi/low sense
    int tmpPin = pins.high;
    pins.high = pins.low;
    pins.low = tmpPin;
    // update voltage
    setPins(pins);
    Serial << "High=" << pins.high << ", Low=" << pins.low;
    Serial.println();
}
