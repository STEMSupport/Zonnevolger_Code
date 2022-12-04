#include <Servo.h> 
#include <DHT.h>
#include <SPI.h>
#include <SD.h>

#define DHTTYPE DHT11  
#define DHTPIN 2  
DHT dht(DHTPIN, DHTTYPE);

Servo horizontaal;
Servo verticaal;

int input[4]={16, 17, 18, 19};

int LU = 0; //pin: 16
int RU = 1; //pin: 17
int LD = 2; //pin: 14
int RD = 3; //pin: 15

int vochtigheid = 4;
int temperatuur = 5;

int horizontaal_hoek = 6;
int verticaal_hoek = 7;
int size_variabelen = 7;

const int chipSelect = 7;

unsigned long start_millis_SD; 
unsigned long start_millis_sensor;
bool horizontaal_set = 0;
bool verticaal_set = 0;
long variabelen[8] = {LU, RU, LD, RD, vochtigheid, temperatuur, horizontaal_hoek, verticaal_hoek};

int read_sensor(int pin){
  int QRE_Value = 0;
  
  pinMode( pin, OUTPUT );
  digitalWrite( pin, HIGH );  
  delayMicroseconds(1250);
  pinMode( pin, INPUT );
  unsigned long time_IR_right = micros();
    
  while (true){; 
    if(!(digitalRead(pin) == HIGH && ((micros() - time_IR_right) < 30000))){
      break; 
    }
  }
  QRE_Value += micros() - time_IR_right;
  pinMode( pin, OUTPUT );
  digitalWrite( pin, HIGH );  

  return(QRE_Value);
}


void setup() {
  variabelen[horizontaal_hoek] = 90;
  variabelen[verticaal_hoek]   = 90;
  for(int i = 0; i<4; i++){
    pinMode(input[i], INPUT_PULLUP);
  }
  Serial.begin(250000);
    
  horizontaal.attach(10);
  verticaal.attach(9);
  horizontaal.write(variabelen[horizontaal_hoek]); 
  verticaal.write(variabelen[verticaal_hoek]);

  dht.begin();

  Serial.print("Initializing SD card...");
  SD.begin(chipSelect);
  start_millis_SD = millis();
  start_millis_sensor = millis();
}

void loop() {
  read_sensors();
  set_servo_horizontaal();
  set_servo_verticaal();  
  write_serial();
  write_SD();

}

void read_sensors(){
  if((millis()- start_millis_sensor) > 30){ //half Fall/rise time LDR
    variabelen[LU] = read_sensor(16);
    variabelen[RU] = read_sensor(17);
    variabelen[RD] = read_sensor(15);
    variabelen[LD] = read_sensor(14);
    variabelen[vochtigheid] = dht.readHumidity();
    variabelen[temperatuur] = dht.readTemperature();
    horizontaal_set = 0;
    verticaal_set = 0;
    start_millis_sensor = millis();
  }
}

void set_servo_horizontaal(){
  if(!horizontaal_set){
    if((variabelen[LU] > variabelen[RU]) && (variabelen[LD] > variabelen[RD])){
        variabelen[horizontaal_hoek] +=1;
    }else if((variabelen[LU] < variabelen[RU]) && (variabelen[LD] < variabelen[RD])){
        variabelen[horizontaal_hoek] -=1;
    }
    if(variabelen[horizontaal_hoek] < 30){
      variabelen[horizontaal_hoek] = 30;
    }else if(variabelen[horizontaal_hoek] > 180){
      variabelen[horizontaal_hoek] = 180;
    }
    horizontaal.write(variabelen[horizontaal_hoek]);
    horizontaal_set = 1;
  }
}

void set_servo_verticaal(){
  if(!verticaal_set){
    if((variabelen[LU] > variabelen[LD]) && (variabelen[RU] > variabelen[RD])){
        variabelen[verticaal_hoek] +=1;
    }else if((variabelen[LU] < variabelen[LD]) && (variabelen[RU] < variabelen[RD])){
        variabelen[verticaal_hoek] -=1;
    }
    if(variabelen[verticaal_hoek] < 30){
      variabelen[verticaal_hoek] = 30;
    }else if(variabelen[verticaal_hoek] > 180){
      variabelen[verticaal_hoek] = 180;
    }
    verticaal.write(variabelen[verticaal_hoek]);
    verticaal_set = 1;
  }
  
}

void write_serial(){
  for(int i = 0; i<size_variabelen; i++){
    Serial.print(variabelen[i]);
    Serial.print(", ");
  }
  Serial.println(variabelen[size_variabelen]);
}

void write_SD(){
  if((millis()- start_millis_SD) > 60000){
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
    if (dataFile) {
      for(int i = 0; i<size_variabelen; i++){
        dataFile.print(variabelen[i]);
        dataFile.print(", ");
      }
      dataFile.print(", ");
      dataFile.println(variabelen[size_variabelen]);
    
      dataFile.close();
      
     }else {
      Serial.println("error opening datalog.txt");
    }
    start_millis_SD = millis();
  }
}
