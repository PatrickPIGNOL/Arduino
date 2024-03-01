#include "OneWire.h"
#include "DallasTemperature.h"
#include "RelaysBoard.h"

OneWire vOneWire1(38);
OneWire vOneWire2(39);
DallasTemperature vDT1(&vOneWire1);
DallasTemperature vDT2(&vOneWire2);
RelaysBoard RelaysBoard(22);

void setup() {
  Serial.begin(9600);  // définition de l'ouverture du port série
  vDT1.begin();          // sonde activée
  vDT2.begin();          // sonde activée
}

void loop() {
  vDT1.requestTemperatures();
  int vT1 = vDT1.getTempCByIndex(0);
  vDT2.requestTemperatures();
  int vT2 = vDT2.getTempCByIndex(0);
 
  Serial.print(vT1);
  Serial.println( "C");
  Serial.print(vT2);
  Serial.println( "C");
 
  delay(1000);
}
