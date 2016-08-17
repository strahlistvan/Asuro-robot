#include "asuro.h"
//globalis valtozok
unsigned int data[2];
unsigned char message[1];
unsigned char speed=75; //sebesseg
unsigned int fekete, feher; //fenyerrossegek
unsigned int feny=50;

void kalibral() {
  LineData(data);
  fekete=data[0];
  feher=data[1];
}

void kikerul(){
  int i,j;
  //eloszor tolat
  MotorDir(RWD,RWD);
  for (i=0; i<200; i++)
    for (j=0; j<1000; j++) {
	  MotorSpeed(100,100);
	}
   for (i=0; i<200; i++) 
     for (j=0; j<1000; j++){
	   MotorSpeed(150,100);
	 }
	 int fenyek[2];
	  while (1) {
	    MotorSpeed(100,150);
		if(fenyek[0]<40)
		  if (fenyek[1]<40) break;
	  }
	  
	 
}

void Kuld() {
	unsigned int i;
	for (i=0; i<65500;i++) SerWrite("1",1);
	for (i=0; i<65500;i++) SerWrite("1",1);
	for (i=0; i<65500;i++) SerWrite("1",1);
	for (i=0; i<65500;i++) SerWrite("1",1);
	message[0]="0";
}
//Varakozas az 1esre es visszavezetes a fekete vonalra

void Varakozas(){
  FrontLED(OFF);
  BackLED(ON,ON);
  SerRead(message,1,0);
  if (message[0]=="1") {
    MotorDir(FWD,FWD);
   // Addig kell mennie, amig legalabb az egyik szenzor feketet olvas
   while (1) {
     MotorSpeed(speed,speed);
     if (data[0]<feny) break; //egyik fekete
     if (data[1]<feny) break; //vagy a masik
    }//while(1) vege
  }//if vege
}

//vizsgalja a fenyerosseget
void VonalKovetes() {
BackLED(OFF,OFF);
FrontLED(ON);
if (data[0]>data[1]) // left brighter than right
{MotorSpeed(speed+25,speed); } // ... speed up left
else
{MotorSpeed(speed,speed+25); } // ... speed up right
}

int main(void) {
  Init();
  kalibral();
  message[0]="0";
  MotorDir(FWD,FWD); 
  while(1){ 
    LineData(data);
    if (data[0]>feny) { //kilepo feltetelEK
     if (data[1]>feny) { 
	   MotorSpeed(0,0);
       Kuld();
       Varakozas();
     }//if vege
    }//if vege
  VonalKovetes();
  if (PollSwitch()>0) kikerul();
  }//while vege
}