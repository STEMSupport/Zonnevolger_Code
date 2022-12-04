//De IR sensoren zijn digitale sensoren, dit wil zeggen dat ze maar 2 waarden gebruiken 0 en 1.
//Deze waarden zijn gedefinieerd als volgt, een waarde van 1 wil zeggen dat er een voltage groter dan 2V 
//op de pin van de Arduino staat. Een waarde van 0 wil zeggen dat er minder dan 2V op de pin van de Arduino staat.
//Om deze fototransistors uit te lezen gaan we eerst een condensator laden tot 5V en dan de tijd meten totdat de Arduinopin een digitale 0 (LOW) uitmeet. 
//Hoe korter deze tijd hoe hoger de intensiteit van het licht dat invalt op de fototransistor.

int read_sensor(int pin){
  pinMode( pin, OUTPUT );
  digitalWrite( pin, HIGH );  
  delayMicroseconds(10);
  pinMode( pin, INPUT );
  long time_IR = micros();

  //meet de tijd tot de arduinopin LOW is.
  while (digitalRead(pin) == HIGH && micros() - time_IR < 30000); 
  int QRE_Value = micros() - time_IR;
  return(QRE_Value);
}


void setup() {
Serial.begin(9600);

}

void loop() {
for (int i= 14; i < 18; i++){
  int value = read_sensor(i);
  Serial.print(String(i));
  Serial.print("= ");
  Serial.print(value);
  Serial.print(",");
}
Serial.println("");
}
