#include "OneWire.h"
#include "DallasTemperature.h"
#include "RelaysBoard.h"

#define ChuntPIN 50
#define PumpPIN 22
#define HeatPIN 24
#define ClimPIN 25
#define FanPIN 26

typedef enum 
{
  TooHot = 33,
  TooCold = 28,
  Average = 30
}Status;

OneWire vOneWire1(38);
OneWire vOneWire2(39);
DallasTemperature vDT1(&vOneWire1);
DallasTemperature vDT2(&vOneWire2);
RelaysBoard RelaysBoard(22);
Status vStatus = Status::Average;
void setup() 
{
  Serial.begin(9600);  // définition de l'ouverture du port série
  vDT1.begin();          // sonde activée
  vDT2.begin();          // sonde activée
  pinMode(ChuntPIN, INPUT);  
  pinMode(PumpPIN, OUTPUT);
  pinMode(HeatPIN, OUTPUT);
  pinMode(ClimPIN, OUTPUT);
  pinMode(FanPIN, OUTPUT);
}

void loop() 
{
  vDT1.requestTemperatures();
  int vT1 = vDT1.getTempCByIndex(0);
  vDT2.requestTemperatures();
  int vT2 = vDT2.getTempCByIndex(0);
 
  Serial.print(vT1);
  Serial.println( "C");
  Serial.print(vT2);
  Serial.println( "C");

  if(vT2 >= Status::TooHot)
  {
    vStatus = Status::TooHot;
  }
  else if(vT2 <= Status::TooCold)
  {
    vStatus = Status::TooCold;
  }
  else if(vT2 >= Status::Average - 1 && vT2 <= Status::Average + 1)
  {
    vStatus = Status::Average;
  }

  if(digitalRead(ChuntPIN) == HIGH)
  {
    digitalWrite(PumpPIN, HIGH);
  
  
    switch(vStatus)
    {
      case Status::TooCold :
      {      
        digitalWrite(HeatPIN, HIGH);
        if(vT1 >= Status::TooHot)
        {
          digitalWrite(ClimPIN, LOW);
        }
        else if(vT1 < Status::Average)
        {
          digitalWrite(ClimPIN, HIGH);
        }
        digitalWrite(FanPIN, HIGH);
      }break;
      case Status::TooHot :
      {
        digitalWrite(HeatPIN, LOW);
        if(vT1 <= Status::TooCold)
        {
          digitalWrite(ClimPIN, LOW);
        }
        else if(vT1 > Status::Average)
        {        
          digitalWrite(ClimPIN, HIGH);
        }
        digitalWrite(FanPIN, HIGH);
      }break;
      case Status::Average :
      default:
      {
        if(vT1 < Status::Average - 1)
        {        
          digitalWrite(HeatPIN, HIGH);
          digitalWrite(ClimPIN, HIGH);
          digitalWrite(FanPIN, HIGH);
        }
        else if(vT1 > Status::Average + 1)      
        {
          digitalWrite(HeatPIN, LOW);        
          digitalWrite(ClimPIN, HIGH);
          digitalWrite(FanPIN, HIGH);
        }
        else
        {
          digitalWrite(ClimPIN, LOW);
          digitalWrite(FanPIN, LOW);
        }
      }break;
    }
  }
  else
  {
    digitalWrite(PumpPIN, LOW);
    digitalWrite(HeatPIN, LOW);        
    digitalWrite(ClimPIN, LOW);
    digitalWrite(FanPIN, LOW);
  }
  delay(500);
}
