
#define LED_PIN 13
const int outLed = 5;
const int inSwitch = 12;
const int levelPin = A5;
int ledLevel = 0;

void setup()
{
    pinMode(outLed, OUTPUT);
    pinMode(inSwitch, INPUT);
    pinMode(levelPin, INPUT);
    Serial.begin(9600);
}

void loop()
{
    //lineRead = analogRead(A0);
    // read pot and convert to TDW %level
    ledLevel = analogRead(levelPin);
    Serial.println(ledLevel);
    ledLevel = map(ledLevel, 0, 1023, 0, 100);
    //int val = ;
    if (digitalRead(inSwitch) != LOW) { 
        //digitalWrite(outLed, HIGH);
        analogWrite(outLed, ledLevel);
        delay(100);
    } else {
        //digitalWrite(outLed, LOW);
        analogWrite(outLed,0);
        delay(100);
    }
    /*
        delay(500);
        digitalWrite(outLed, LOW);
        delay(5000);
    */
}
