#include "OneWire.h"
#include "DallasTemperature.h"
#include "RelaysBoard.h"

#define PumpPIN 22
#define FanPIN 23
#define HeatPIN 24
#define ClimPIN 25
#define PrimairePIN 27
#define SecondairePIN 29
#define FinishPIN 29
#define TemperaturePIN1 52
#define TemperaturePIN2 53
#define JoursFermentationPrimaire 15
#define JoursFermentationSecondaire 15

bool vFermentationSecondaire = false;

typedef enum
{
  FermentationPrimaire,
  FermentationSecondaire,
  EndOfFermentation
} EStatus;

typedef enum
{
  PrimaireTooHot = 33,
  PrimaireTooCold = 28,
  PrimaireAverage = 30,
  PrimaireTolerance = 6
} EFermentationPrimaire;

typedef enum
{
  SecondaireTooHot = 22,
  SecondaireTooCold = 18,
  SecondaireAverage = 20,
  SecondaireTolerance = 1
} EFermentationSecondaire;

OneWire vOneWire1(TemperaturePIN1);
OneWire vOneWire2(TemperaturePIN2);
DallasTemperature vDT1(&vOneWire1);
DallasTemperature vDT2(&vOneWire2);
RelaysBoard RelaysBoard(22);
EStatus vStatus = EStatus::FermentationPrimaire;
int vTemperatureStatus = EFermentationPrimaire::PrimaireAverage;
long vCounter = 0;
void setup()
{
  Serial.begin(9600);  // définition de l'ouverture du port série
  vDT1.begin();          // sonde activée
  vDT2.begin();          // sonde activée
  pinMode(PumpPIN, OUTPUT);
  pinMode(HeatPIN, OUTPUT);
  pinMode(ClimPIN, OUTPUT);
  pinMode(FanPIN, OUTPUT);
  pinMode(PrimairePIN, OUTPUT);
  pinMode(SecondairePIN, OUTPUT);
  pinMode(FinishPIN, OUTPUT);
  digitalWrite(PrimairePIN, HIGH);
  digitalWrite(SecondairePIN, LOW);
  digitalWrite(FinishPIN, LOW);
  digitalWrite(HeatPIN, LOW);
  digitalWrite(ClimPIN, LOW);
  digitalWrite(PumpPIN, HIGH);
  digitalWrite(FanPIN, HIGH);
}

long mMillisecondToDays(long pCounter)
{
  return pCounter / 86400000; // (24 * 3600 * 1000)
}

void loop()
{
  vCounter += 500;

  if (vFermentationSecondaire)
  {
    if ((vStatus != EStatus::FermentationSecondaire && vStatus != EStatus::EndOfFermentation) && mMillisecondToDays(vCounter) < JoursFermentationPrimaire)
    {
      vStatus = EStatus::FermentationPrimaire;
      digitalWrite(PrimairePIN, HIGH);
    }
    else if ((vStatus != EStatus::FermentationSecondaire && vStatus != EStatus::EndOfFermentation) && mMillisecondToDays(vCounter) > JoursFermentationPrimaire)
    {
      vStatus = EStatus::FermentationSecondaire;
      digitalWrite(PrimairePIN, LOW);
      digitalWrite(SecondairePIN, HIGH);
    }
    else if ((vStatus != EStatus::EndOfFermentation) && mMillisecondToDays(vCounter) > JoursFermentationPrimaire + JoursFermentationSecondaire)
    {
      vStatus = EStatus::EndOfFermentation;

      digitalWrite(PrimairePIN, LOW);
      digitalWrite(SecondairePIN, LOW);
      digitalWrite(FinishPIN, HIGH);
    }
  }
  else
  {
    if
    (
      vStatus != EStatus::EndOfFermentation
      &&
      mMillisecondToDays(vCounter) < JoursFermentationPrimaire
    )
    {
      vStatus = EStatus::FermentationPrimaire;
    }
    else if (vStatus != EStatus::EndOfFermentation && mMillisecondToDays(vCounter) > JoursFermentationPrimaire)
    {
      vStatus = EStatus::EndOfFermentation;
    }
    else if (vStatus == EStatus::EndOfFermentation)
    {
      vStatus = vStatus = EStatus::EndOfFermentation;
    }
  }

  vDT1.requestTemperatures();
  int vTemperature1 = vDT1.getTempCByIndex(0);
  vDT2.requestTemperatures();
  int vTemperature2 = vDT2.getTempCByIndex(0);


  Serial.print("Clim Temp: ");
  Serial.print(vTemperature1);
  Serial.println( "°C");
  Serial.print("Beer Temp: ");
  Serial.print(vTemperature2);
  Serial.println( "°C");



  switch (vStatus)
  {
    case EStatus::FermentationPrimaire:
      {
        if (vTemperature2 >= EFermentationPrimaire::PrimaireTooHot)
        {
          vTemperatureStatus = EFermentationPrimaire::PrimaireTooHot;
        }
        else if (vTemperature2 <= EFermentationPrimaire::PrimaireTooCold)
        {
          vTemperatureStatus = EFermentationPrimaire::PrimaireTooCold;
        }
        else if
        (
          vTemperature2 >= EFermentationPrimaire::PrimaireAverage - EFermentationPrimaire::PrimaireTolerance
          &&
          vTemperature2 <= EFermentationPrimaire::PrimaireAverage + EFermentationPrimaire::PrimaireTolerance
        )
        {
          vTemperatureStatus = EFermentationPrimaire::PrimaireAverage;
        }
        switch (vTemperatureStatus)
        {
          case EFermentationPrimaire::PrimaireTooCold :
            {
              digitalWrite(HeatPIN, HIGH);
              if (vTemperature1 >= EFermentationPrimaire::PrimaireTooHot)
              {
                digitalWrite(ClimPIN, LOW);
              }
              else if (vTemperature1 < EFermentationPrimaire::PrimaireAverage)
              {
                digitalWrite(ClimPIN, HIGH);
              }
            } break;
          case EFermentationPrimaire::PrimaireTooHot :
            {
              digitalWrite(HeatPIN, LOW);
              if (vTemperature1 <= EFermentationPrimaire::PrimaireTooCold)
              {
                digitalWrite(ClimPIN, LOW);
              }
              else if (vTemperature1 > EFermentationPrimaire::PrimaireAverage)
              {
                digitalWrite(ClimPIN, HIGH);
              }
            } break;
          case EFermentationPrimaire::PrimaireAverage :
          default:
            {
              if (vTemperature1 < EFermentationPrimaire::PrimaireAverage - EFermentationPrimaire::PrimaireTolerance)
              {
                digitalWrite(HeatPIN, HIGH);
                digitalWrite(ClimPIN, HIGH);
              }
              else if (vTemperature1 > EFermentationPrimaire::PrimaireAverage + EFermentationPrimaire::PrimaireTolerance)
              {
                digitalWrite(HeatPIN, LOW);
                digitalWrite(ClimPIN, HIGH);
              }
              else
              {
                digitalWrite(ClimPIN, LOW);
              }
            } break;
        }
      } break;
    case EStatus::FermentationSecondaire:
    case EStatus::EndOfFermentation:
      {
        if (vFermentationSecondaire)
        {
          if (vTemperature2 >= EFermentationSecondaire::SecondaireTooHot)
          {
            vTemperatureStatus = EFermentationSecondaire::SecondaireTooHot;
          }
          else if (vTemperature2 <= EFermentationSecondaire::SecondaireTooCold)
          {
            vTemperatureStatus = EFermentationSecondaire::SecondaireTooCold;
          }
          else if
          (
            vTemperature2 >= EFermentationSecondaire::SecondaireAverage - EFermentationSecondaire::SecondaireTolerance
            &&
            vTemperature2 <= EFermentationSecondaire::SecondaireAverage + EFermentationSecondaire::SecondaireTolerance
          )
          {
            vTemperatureStatus = EFermentationSecondaire::SecondaireAverage;
          }
          switch (vTemperatureStatus)
          {
            case EFermentationSecondaire::SecondaireTooCold :
              {
                digitalWrite(HeatPIN, HIGH);
                if (vTemperature1 >= EFermentationSecondaire::SecondaireTooHot)
                {
                  digitalWrite(ClimPIN, LOW);
                }
                else if (vTemperature1 < EFermentationSecondaire::SecondaireAverage)
                {
                  digitalWrite(ClimPIN, HIGH);
                }
              } break;
            case EFermentationSecondaire::SecondaireTooHot :
              {
                digitalWrite(HeatPIN, LOW);
                if (vTemperature1 <= EFermentationSecondaire::SecondaireTooCold)
                {
                  digitalWrite(ClimPIN, LOW);
                }
                else if (vTemperature1 > EFermentationSecondaire::SecondaireAverage)
                {
                  digitalWrite(ClimPIN, HIGH);
                }
              } break;
            case EFermentationSecondaire::SecondaireAverage :
            default:
              {
                digitalWrite(ClimPIN, HIGH);
                if (vTemperature1 < EFermentationSecondaire::SecondaireAverage - EFermentationSecondaire::SecondaireTolerance)
                {
                  digitalWrite(HeatPIN, HIGH);
                }
                else if (vTemperature1 > EFermentationSecondaire::SecondaireAverage + EFermentationSecondaire::SecondaireTolerance)
                {
                  digitalWrite(HeatPIN, LOW);
                }
              } break;
          }

          if (vTemperature2 >= EFermentationSecondaire::SecondaireTooHot)
          {
            vTemperatureStatus = EFermentationSecondaire::SecondaireTooHot;
          }
          else if (vTemperature2 <= EFermentationSecondaire::SecondaireTooCold)
          {
            vTemperatureStatus = EFermentationSecondaire::SecondaireTooCold;
          }
          else if
          (
            vTemperature2 >= EFermentationSecondaire::SecondaireAverage - EFermentationSecondaire::SecondaireTolerance
            &&
            vTemperature2 <= EFermentationSecondaire::SecondaireAverage + EFermentationSecondaire::SecondaireTolerance
          )
          {
            vTemperatureStatus = EFermentationSecondaire::SecondaireAverage;
          }
          switch (vTemperatureStatus)
          {
            case EFermentationSecondaire::SecondaireTooCold :
              {
                digitalWrite(HeatPIN, HIGH);
                if (vTemperature1 >= EFermentationSecondaire::SecondaireTooHot)
                {
                  digitalWrite(ClimPIN, LOW);
                }
                else if (vTemperature1 < EFermentationSecondaire::SecondaireAverage)
                {
                  digitalWrite(ClimPIN, HIGH);
                }
              } break;
            case EFermentationSecondaire::SecondaireTooHot :
              {
                digitalWrite(HeatPIN, LOW);
                if (vTemperature1 <= EFermentationSecondaire::SecondaireTooCold)
                {
                  digitalWrite(ClimPIN, LOW);
                }
                else if (vTemperature1 > EFermentationSecondaire::SecondaireAverage)
                {
                  digitalWrite(ClimPIN, HIGH);
                }
              } break;
            case EFermentationSecondaire::SecondaireAverage :
            default:
              {
                digitalWrite(ClimPIN, HIGH);
                if (vTemperature1 < EFermentationSecondaire::SecondaireAverage - EFermentationSecondaire::SecondaireTolerance)
                {
                  digitalWrite(HeatPIN, HIGH);
                }
                else if (vTemperature1 > EFermentationSecondaire::SecondaireAverage + EFermentationSecondaire::SecondaireTolerance)
                {
                  digitalWrite(HeatPIN, LOW);
                }
              } break;
          }
        } break;
      }
  }
  delay(500);
}
