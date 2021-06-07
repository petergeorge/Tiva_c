#include<SPI.h>
#define LEDpin 7
volatile boolean received;
char Slavereceived;
char Masterreceived;

void setup()
{
  Serial.begin(9600);
  pinMode(LEDpin,OUTPUT);                 // Setting pin 7 as OUTPU
  SPCR |= (1<<SPE)| (1<<SPIE);            //Turn on SPI in Slave Mode
  received = false;
  SPI.attachInterrupt();                  //Interuupt ON is set for SPI commnucation
  sei();
}

ISR (SPI_STC_vect)                        //Inerrrput routine function 
{
  Slavereceived = SPI.transfer(Slavereceived);         // Value received from master if store in variable slavereceived
  received = true;                        //Sets received as True 
}

void loop()
{  
  if(received)   //Logic to SET LED ON OR OFF depending upon the value recerived from master
   {
      if (Slavereceived=='A') 
      {
        digitalWrite(LEDpin,HIGH);         //Sets pin 7 as HIGH LED ON
        Serial.println("Slave LED ON");
        Serial.println(Slavereceived);
        SPI.transfer(Slavereceived); 
      }
       else
      {
        digitalWrite(LEDpin,LOW);          //Sets pin 7 as LOW LED OFF
        Serial.println("Slave LED OFF");
        Serial.println(Slavereceived);
        //SPI.transfer(Slavereceived); 

      } 
   }
   delay(1000);
}
