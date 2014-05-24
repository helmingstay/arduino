// Insertion style streaming to Serial
template<class T> inline Print &operator <<(Print &obj, T arg) { 
    obj.print(arg); return obj; 
} 

bool debounceBool(const int readPin, const int debounceTime, const bool debug=false) {
    // adapted from http://arduino.cc/en/Tutorial/Debounce
    // returns true if readpin stays HIGH for at least debounceTime
    //
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
        if( initState != readState) {
            // reset the timer on change, 
            // update state
            debounceTimer = millis();
            initState = readState;
        }
    }
    // write output
    if (readState == HIGH) {
        return true;
    } else { 
        return false;
    }
}
