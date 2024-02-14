#include "FreqPeriodCounter.h"
#include <SoftwareSerial.h>
SoftwareSerial XBee(2,3);
const byte counterPin = A0; 
const byte counterInterrupt = A1; // = d3
FreqPeriodCounter counter(counterPin, micros);
 
void setup(void) 
{ attachInterrupt(counterInterrupt, counterISR, CHANGE);
  Serial.begin(9600);
      pinMode(A0, INPUT);
      XBee.begin(9600);
}
 
void loop(void) 
{ 
  int c=analogRead(A0);
  //Serial.println(c);
  if(c==0)
  {
  for(int i=0;i<1024;i++)
   {
    c=analogRead(A0);
    Serial.println(c);
    XBee.write(c);
   }
    digitalWrite(A1,LOW);
  int period;
  if(counter.ready()) period = counter.period; 
  Serial.println((float)1/period);
  c=abs((float)1/period);
  XBee.write(c);
  digitalWrite(A1,HIGH);
  //delay(1000);
  }
}
 
void counterISR()
{ counter.poll();
}
