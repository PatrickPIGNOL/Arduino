#define ON LOW
#define OFF HIGH

const int gRelaysCount = 16;
int gRelays[gRelaysCount];
int gRelaysFirstPin = 22;
int gState = OFF;
int gLed = 13;
int gDelay = 50;

void setup() 
{  
  Serial.begin(9600);
  pinMode(gLed, OUTPUT);
  digitalWrite(gLed, LOW);
  int i = 0;
  while(i < gRelaysCount)  
  {   
    gRelays[i]= gRelaysFirstPin + i;
    pinMode(gRelays[i], OUTPUT);
    digitalWrite(gRelays[i], gState);
    i++;
  }
  randomSeed(10);
}

void loop() 
{
  if(gState == ON)
  {
    gState = OFF;
  }
  else
  {
    gState = ON;
  }
  digitalWrite(gLed, gState);
  int i = 0;
  while(i < gRelaysCount)
  {   
      //Serial.println(ON);
      //Serial.println(i);
      digitalWrite(gRelays[i], ON);
      delay(gDelay);
      i++;
  }  
  i = 0;
  while(i < gRelaysCount)
  {   
      //Serial.println(i);
      digitalWrite(gRelays[i], OFF);
      delay(gDelay);
      i++;
  }
  i = 0;
  while(i < gRelaysCount)
  {   
    int j = gRelaysCount -1;
    while(j > i)
    {   
        //Serial.println(i);
        digitalWrite(gRelays[j], ON);
        delay(gDelay);
        digitalWrite(gRelays[j], OFF);
        delay(gDelay);
        j--;
    }
      //Serial.println(i);
      digitalWrite(gRelays[i], ON);
      delay(gDelay);
      i++;
  }
  i = 0;
  while(i < gRelaysCount)
  {   
    int j = gRelaysCount -1;
    while(j > i)
    {   
        //Serial.println(i);
        digitalWrite(gRelays[j], OFF);
        delay(gDelay);
        digitalWrite(gRelays[j], ON);
        delay(gDelay);
        j--;
    }
      //Serial.println(i);
      digitalWrite(gRelays[i], OFF);
      delay(gDelay);
      i++;
  }
  int vRelays[gRelaysCount];
  while(i < gRelaysCount)
  {
    vRelays[i] = 0;
    i++;
  }
  i = 0;
  bool vContinue = true;
  while(vContinue && (i < gRelaysCount))
  {
    int vRandNumber = random(gRelaysCount);
    int j = 0;
    while(j < i)
    {
      if(gRelaysFirstPin + vRandNumber == vRelays[j])
      {
        vRandNumber = random(gRelaysCount);
        j = -1;
      }
      j++;
    }
    vRelays[i] = gRelaysFirstPin + vRandNumber;
    i++;
  }
  i = 0;
  while(i < gRelaysCount)
  {   
        digitalWrite(vRelays[i], ON);
        delay(gDelay);
        digitalWrite(vRelays[i], OFF);
        delay(gDelay);
        i++;
  }
  i = 0;
  while(i < gRelaysCount)
  {   
        //Serial.println(i);
        digitalWrite(vRelays[i], ON);
        delay(gDelay);
        i++;
  }  
  i = 0;
  while(i < gRelaysCount)
  {   
        digitalWrite(vRelays[i], OFF);
        delay(gDelay);
        i++;
  }
}
