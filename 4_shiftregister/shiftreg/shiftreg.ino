//Pin verbonden met ST_CP van het shiftregister
int latchPin = 3;
//Pin verbonden met SH_CP van het shiftregister
int clockPin = 4;
//Pin verbonden met DS van het shiftregister
int dataPin = 5;
void setup() {
//Zet de gebruikte pinnen op output
pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(dataPin, OUTPUT);
}
void loop() {
//Laat alle LED's van links naar rechts oplichten zonder for loop

// Zet de latchpin LOW zodat de actieve pinnen niet worden aangepast tijdens het zenden van de nieuwe bits.
digitalWrite(latchPin, LOW);
// zend de nieuwe bits.
shiftOut(dataPin, clockPin, MSBFIRST, 0b1000000);
//Zet de latchpin HIGH zodat de geselecteerde pinnen worden geactiveerd.
digitalWrite(latchPin, HIGH);
// korte pauze:
delay(500);

// Voor de overige 7 pinnen exact hetzelfde
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 0b0100000);
digitalWrite(latchPin, HIGH);
delay(500);


digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 0b0010000);
digitalWrite(latchPin, HIGH);
delay(500);

digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 0b0001000);
digitalWrite(latchPin, HIGH);
delay(500);

digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 0b0000100);
digitalWrite(latchPin, HIGH);
delay(500);

digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 0b00000010);
digitalWrite(latchPin, HIGH);
delay(500);

digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 0b0000001);
digitalWrite(latchPin, HIGH);
delay(500);

digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, 0b0000000);
digitalWrite(latchPin, HIGH);
delay(500);

}
