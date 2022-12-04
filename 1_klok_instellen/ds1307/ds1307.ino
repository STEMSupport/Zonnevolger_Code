//Run deze code één maal om de klok te starten en de tijd de sycroniseren met de verbonden computer

#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Zondag", "Maandag", "Dinsdag", "Woensdag", "Donderdag", "Vrijdag", "Zaterdag"}; 
void setup () {
 Serial.begin(9600);
 Serial.println("serial");
 if (! rtc.begin()) {
   Serial.println("Kan klok niet vinden");
   while (1);
 }

 rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

}
void loop () {
 DateTime now = rtc.now();
 Serial.print(now.year(), DEC);
 Serial.print('/');
 Serial.print(now.month(), DEC);
 Serial.print('/');
 Serial.print(now.day(), DEC);
 Serial.print(" (");
 Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
 Serial.print(") ");
 Serial.print(now.hour(), DEC);
 Serial.print(':');
 Serial.print(now.minute(), DEC);
 Serial.print(':');
 Serial.print(now.second(), DEC);
 Serial.println();

 //https://nl.wikipedia.org/wiki/Unix_Epoch
 Serial.print(" since midnight 1/1/1970 = ");
 Serial.print(now.unixtime());
 Serial.print("s = ");
 Serial.print(now.unixtime() / 86400L);
 Serial.println("d");
 Serial.println();
 delay(3000);
}
