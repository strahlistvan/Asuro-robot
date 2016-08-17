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
	      if (data[0]<feny) break; //ha egyik fekete akkor break
	      if (data[1]<feny) break; //vagy a masik akkor is break
	    }//while(1) vege
	}//if vege
}

//vizsgalja a fenyerosseget
void VonalKovetes() {
	BackLED(OFF,OFF);
	FrontLED(ON);
	if (data[0]>data[1]) // left brighter than right
	{MotorSpeed(speed+25,speed); } // ... speed up left motor
	else
	{MotorSpeed(speed,speed+25); } // ... speed up right motor
}

int main(void) {
	Init();
	kalibral();
	message[0]="0";
	Varakozas();
	FrontLED(ON); // Switch ON line trace illumination
	while(1){ // Eternal loop, ASURO should follow
	   LineData(data);
	   VonalKovetes();
	   if (data[0]>feny+20) { //kilepo feltetelek
	    if (data[1]>feny+20) { MotorSpeed(0,0);
	    Kuld();
	    Varakozas();
	    }//if
	   }//if
	}//while
	return 0;
}