#include "asuro.h"
void Bulaj(){
	/*int r=rand()%7;
	switch (r) {
	case 0: {goto elso; break;}
	case 2: {goto masodik; break;}
	case 4: {goto otodik; break;}
	case 3: {goto negyedik; break;}
	case 1: {goto harmadik; break;}
	case 5: {goto hatodik; break;}
	case 6: { goto hetedik; break;}
	default: { goto elso; break; }
	}*/
	int i,j,k;
	//Helyben forgas jobbra
	elso:
	MotorDir(FWD,RWD);
	for(i=0;i<400;i++){
	for(j=0;j<1000;j++){
	MotorSpeed(111,111);
	}
	}
	//Led villogtatas felvaltva a ket ledet
	masodik:
	for(i=0;i<5;i++){
	for(j=0;j<65500;j++)
	BackLED(OFF,ON);
	for(k=0;k<65500;k++)
	BackLED(ON,OFF);
	}
	//Helyben forgas balra
	harmadik:
	MotorDir(RWD,FWD);
	for(i=0;i<400;i++){
	for(j=0;j<1000;j++){
	MotorSpeed(200,200);
	}
	}
	//Itt kene random kolbaszolni
	negyedik:
	for(k=0;k<20;k++){
	//r1= (1.FWD,2.RWD,3.BREAK) bal oldali motornak
	//r2= (1.FWD,2.RWD,3.BREAK) jobb oldali motornak
	int r1=rand()%3+1; //sorsol 13ig
	int r2=rand()%3+1; //sorsol 13ig
	//Veletlen iranyba allitjuk m2 motort kulon
	if(r1==1){
	if(r2==1) MotorDir(FWD,FWD);
	if(r2==2) MotorDir(FWD,RWD);
	if(r2==3) MotorDir(FWD,BREAK);
	}
	else if(r1==2){
	if(r2==1) MotorDir(RWD,FWD);
	if(r2==2) MotorDir(RWD,RWD);
	if(r2==3) MotorDir(RWD,BREAK);
	}
	else if(r1==3){
	if(r2==1) MotorDir(BREAK,FWD);
	if(r2==2) MotorDir(BREAK,RWD);
	if(r2==3) MotorDir(FWD,RWD); //ne legyen tetlen
	}
	//Motor sebesseget sorsolunk m2 motornak kulon
	int s1=rand()%255+1; //sorsol 1255ig
	int s2=rand()%255+1; //sorsol 1255ig
	//kb 4mp veletlen koszalas
	for(i=0;i<300;i++){
	for(j=0;j<1000;j++){
	MotorSpeed(s1,s2);
	}
	}
	}//random kószálás vége k ciklus
	//Led villogtatas mind a ket ledet
	otodik:
	for(i=0;i<5;i++){
	for(j=0;j<65500;j++) BackLED(ON,ON);
	for(k=0;k<65500;k++) BackLED(OFF,OFF);
	}
	//Hullammozgas hatrafele
	hatodik:
	MotorDir(RWD,RWD);
	unsigned char sebesseg=rand()%100+100;
	for (k=0; k<10; k++) { //10-szer csinalja meg, tehat 10 hullam lesz
	for (i=0; i<10; i++)
	for (j=0; i<60000; i++) MotorSpeed(sebesseg,0);
	for (i=0; i<10; i++)
	for (j=0; i<60000; i++) MotorSpeed(0,sebesseg);
	}
	//Szaladgal elore hatra gyorsan, kozben szirenazva villog
	hetedik:
	MotorDir(FWD,FWD);
	for (j=0; j<10; j++) {
	for (i=0; i<10000; i++) { MotorSpeed(255,255); BackLED(ON,OFF); }
	for (i=0; i<10000; i++) { MotorSpeed(255,255); BackLED(OFF,ON); }
	}
	MotorDir(RWD,RWD);
	for (j=0; j<10; j++) {
	for (i=0; i<10000; i++) { MotorSpeed(255,255); BackLED(ON,OFF); }
	for (i=0; i<10000; i++) { MotorSpeed(255,255); BackLED(OFF,ON); }
	}
}

//Nehany valtozo
int data[2];
int speed=222; //gyors lesz!
int feny=50;

void VonalKovetes() {
	BackLED(OFF,OFF);
	FrontLED(ON);
	if (data[0]>data[1]) 
	{MotorSpeed(speed+25,speed); } 
	else
	{MotorSpeed(speed,speed+25); } 
}

int main() {
while(1){ 
	   LineData(data);
	   VonalKovetes();
	   if (data[0]>feny+20) { //kilepo feltetelek
	    if (data[1]>feny+20) { 
		  MotorSpeed(0,0);
		  for (;;) {Bulaj();}
	    }//if
	   }//if
	  
	}//while

return 0; 
}
