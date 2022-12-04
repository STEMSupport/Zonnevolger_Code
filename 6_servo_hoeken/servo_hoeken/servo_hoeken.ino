#include <Servo.h> 
Servo horizontaal;
Servo verticaal;

int horizontaal_hoek = 0;
int verticaal_hoek = 0;



void setup() {
  horizontaal.attach(10);
  verticaal.attach(9);
  horizontaal.write(horizontaal_hoek); 
  verticaal.write(verticaal_hoek);
}

void loop() {
  horizontaal.write(horizontaal_hoek); 
  verticaal.write(verticaal_hoek);
  if(horizontaal_hoek >= 180){
      horizontaal_hoek = 0;

  }else {
      horizontaal_hoek++;
  }

  if(verticaal_hoek >= 180){
      verticaal_hoek = 0;

  }else {
      verticaal_hoek++;
  }
  delay(50);
 

}
