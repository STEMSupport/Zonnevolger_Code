int sensorPin = 20;
float sensorValue = 0;
float volt = 0;

void setup() {
pinMode(sensorPin, INPUT);
Serial.begin(9600);

}

void loop() {
 sensorValue = analogRead(sensorPin);
 volt = sensorValue/1023*5;
 Serial.print("volt= ");
 Serial.println(volt); 
 delay(500);

}
