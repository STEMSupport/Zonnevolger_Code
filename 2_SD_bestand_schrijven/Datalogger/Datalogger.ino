//Deze code leest analoge pin 20 uit en schrijft de waarde naar het bestand datalog.txt op de SD kaart.
#include <SPI.h>
#include <SD.h>

const int chipSelect = 7; //Pin 7 activeerd de SD-kaart

void setup() {
  Serial.begin(9600);
  Serial.print("Laad SD kaart");

  // controleer of er een SD kaart aanwezig is:
  if (!SD.begin(chipSelect)) {
    Serial.println("SD error, of SD-kaart niet aanwezig");
    // STOP alles met oneindige lus:
    while (1);
  }
  Serial.println("SD kaart geladen");
}

void loop() {
  // Maak een  string die later naar de SD kaart wordt geschreven:
  String dataString = "";

  // Lees analoge pin 20
   int sensor = analogRead(20);
   dataString += String(sensor);

  // open het bestand, let op er kan maar één bestand geopend zijn.
  // Om een tweede bestand te openen moet je eerst het eerste bestand sluiten.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // Als het bestand geopend is, schrijf naar het bestand:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  // Als het bestand niet geopend is geef een error:
  else {
    Serial.println("error tijdens openen datalog.txt");
  }
}
