#include "OneWire.h"
#include "DallasTemperature.h"


#define LedPIN 13
#define PumpPIN 22
#define FanPIN 23
#define ClimPIN 24
#define ControlPIN 25
#define HeatPIN 26
#define CoolPIN 27
#define PrimairePIN 37
#define SecondairePIN 36
#define FinishPIN 35
#define TemperaturePIN1 52
#define TemperaturePIN2 53
#define JoursFermentationPrimaire 15
#define JoursFermentationSecondaire 1

#define ON LOW
#define OFF HIGH

const int FermentationPrimaireTooHot = 20;
const int FermentationPrimaireTooCold = 17;
const int FermentationPrimaireAverage = 18;
const int FermentationPrimaireTolerance = 1;

const int FermentationSecondaireTooHot = 20;
const int FermentationSecondaireTooCold = 17;
const int FermentationSecondaireAverage = 18;
const int FermentationSecondaireTolerance = 1;

bool vFermentationSecondaire = false;

bool vIsHeating = false;
bool vControlLed = false;

typedef enum
{
    FermentationPrimaire,
    FermentationSecondaire,
    EndOfFermentation
} EStatus;

OneWire vOneWire1(TemperaturePIN1);
OneWire vOneWire2(TemperaturePIN2);
DallasTemperature vDT1(&vOneWire1);
DallasTemperature vDT2(&vOneWire2);
EStatus vStatus = EStatus::FermentationPrimaire;
int vTemperatureStatus = FermentationPrimaireAverage;
long vCounter = 0;
void setup()
{
    Serial.begin(9600);  // définition de l'ouverture du port série
    vDT1.begin();          // sonde activée
    vDT2.begin();          // sonde activée
    pinMode(LedPIN, OUTPUT);
    pinMode(PumpPIN, OUTPUT);
    pinMode(HeatPIN, OUTPUT);
    pinMode(ClimPIN, OUTPUT);
    pinMode(FanPIN, OUTPUT);
    pinMode(ControlPIN, OUTPUT);
    pinMode(HeatPIN, OUTPUT);
    pinMode(CoolPIN, OUTPUT);
    pinMode(PrimairePIN, OUTPUT);
    pinMode(SecondairePIN, OUTPUT);
    pinMode(FinishPIN, OUTPUT);
    digitalWrite(PrimairePIN, ON);
    digitalWrite(SecondairePIN, OFF);
    digitalWrite(FinishPIN, OFF);
    digitalWrite(HeatPIN, ON);
    digitalWrite(ControlPIN, ON);
    digitalWrite(HeatPIN, OFF);
    digitalWrite(ClimPIN, OFF);
    digitalWrite(PumpPIN, ON);
    digitalWrite(FanPIN, ON);
}

long mMillisecondToDays(long pCounter)
{
  return pCounter / 86400000; // (24 * 3600 * 1000)
}

void mSetHeating(bool pHeating)
{
    if((pHeating && !vIsHeating) || (!pHeating && vIsHeating))
    {  
        digitalWrite(ControlPIN, OFF);
        delay(5);
        if(pHeating && !vIsHeating)
        {
            digitalWrite(HeatPIN, ON);
            digitalWrite(CoolPIN, OFF);
        }
        else
        {
            digitalWrite(HeatPIN, OFF);
            digitalWrite(CoolPIN, ON);
        }
        delay(5);
        digitalWrite(ControlPIN, ON);
    }
}

void loop()
{
    vCounter += 500;

    if (vControlLed)
    {
        vControlLed = false;
        digitalWrite(LedPIN, LOW);
    }
    else
    {
        vControlLed = true;
        digitalWrite(LedPIN, HIGH);
    }

    if (vFermentationSecondaire)
    {
        if ((vStatus != EStatus::FermentationSecondaire && vStatus != EStatus::EndOfFermentation) && mMillisecondToDays(vCounter) < JoursFermentationPrimaire)
        {
            vStatus = EStatus::FermentationPrimaire;
            digitalWrite(PrimairePIN, ON);
        }
        else if ((vStatus != EStatus::EndOfFermentation) && mMillisecondToDays(vCounter) > JoursFermentationPrimaire + JoursFermentationSecondaire)
        {
            vStatus = EStatus::EndOfFermentation;
            digitalWrite(PrimairePIN, OFF);
            digitalWrite(SecondairePIN, OFF);
            digitalWrite(FinishPIN, ON);
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

    if (vTemperature2 >= FermentationPrimaireTooHot)
    {
        vTemperatureStatus = FermentationPrimaireTooHot;
    }
    else if (vTemperature2 <= FermentationPrimaireTooCold)
    {
        vTemperatureStatus = FermentationPrimaireTooCold;
    }
    else if
    (
        vTemperature2 >= FermentationPrimaireAverage - FermentationPrimaireTolerance
        &&
        vTemperature2 <= FermentationPrimaireAverage + FermentationPrimaireTolerance
    )
    {
        vTemperatureStatus = FermentationPrimaireAverage;
    }
    switch (vTemperatureStatus)
    {
        case FermentationPrimaireTooCold :
        {
            mSetHeating(true);
            digitalWrite(ClimPIN, ON);
        } break;
        case FermentationPrimaireTooHot :
        {
            mSetHeating(false);
            digitalWrite(ClimPIN, ON); 
        } break;
        case FermentationPrimaireAverage :
        default:
        {
            if (vTemperature2 < FermentationPrimaireAverage)
            {
                mSetHeating(true);
                digitalWrite(ClimPIN, ON);
            }
            else if (vTemperature2 > FermentationPrimaireAverage)
            {
                mSetHeating(false);
                digitalWrite(ClimPIN, ON);
            }
            else if(vTemperature2 == FermentationPrimaireAverage)
            {
                digitalWrite(ClimPIN, OFF);
            }
        } break;
    }
    delay(500);
}
