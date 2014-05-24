// Insertion style streaming to Serial
template<class T> inline Print &operator <<(Print &obj, T arg) { 
    obj.print(arg); return obj; 
} 

bool debounceBool(const int readPin, const int debounceTime, const int trueVal=HIGH, const bool debug=false) {
  // adapted from http://arduino.cc/en/Tutorial/Debounce
    // initialize button reading 
    // we will compare readings to initial state
    int initState = digitalRead(readPin);
    int readState = initState;
    // initialize debounce timer
    int debounceTimer = millis();
    if (debug) {
        Serial << 
        "Timer: " <<  debounceTimer << 
        ", " << "initState: " << initState;
    }
 
    // keep reading until no change for one delay
    while(
        (millis() - debounceTimer) < debounceTime
    ) {
        readState = digitalRead(readPin);
        //Serial.println(readState);
        // reset the timer on change, 
        // update state
        if( initState != readState) {
            debounceTimer = millis();
            initState = readState;
        }
    }
    // need a delay here to ensure we don't 
    // hop back in right away
    // delay(debounceTime);
    // write output
    if (readState == trueVal) {
        return true;
    } else { 
        return false;
    }
}
