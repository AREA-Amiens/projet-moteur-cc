#include <Arduino.h>
#include <MsTimer2.h>

int nbPas=0;

void IntrerrupTimer(){
  int pas =nbPas;
  nbPas=0;
  //Serial1.print('1');
//  Serial1.println(pas);
}

//byte a=0;
void up(){
  if(digitalRead(15))nbPas++;
  else nbPas--;
}
int interpretation(int caractere){
  int interprete;
  switch (caractere) {
    case (int)'0':
    interprete=0;
    break;
    case (int)'1':
    interprete=1;
    break;
    case (int)'2':
    interprete=2;
    break;
    case (int)'3':
    interprete=3;
    break;
    case (int)'4':
    interprete=4;
    break;
    case (int)'5':
    interprete=5;
    break;
    case (int)'6':
    interprete=6;
    break;
    case (int)'7':
    interprete=7;
    break;
    case (int)'8':
    interprete=8;
    break;
    case (int)'9':
    interprete=9;
    break;
    case 0x0D:
    interprete=0x0D;
    break;
  }
  return interprete;
}
int tr=10;
int trans[]={0,0,0,0,0,0,0,0,0,0};
int com=0;
int pwm=0;
int frequancePWM=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(15,INPUT_PULLUP);//trigeur ap2
  pinMode(14,INPUT_PULLUP);//ap2
  pinMode(20,OUTPUT);
  pinMode(19,OUTPUT);
  digitalWrite(19,HIGH);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  attachInterrupt(digitalPinToInterrupt(14),up,RISING);
  Serial1.begin(9600);
  Serial.begin(9600);

  Serial1.println("teset 1");
  MsTimer2::set(100,IntrerrupTimer);//tout les  seconde
  MsTimer2::start();

  //analogWrite(20,128);
}

void loop() {
  if ( Serial1.available() ) {
    int lu = Serial1.read();
    char interprete;
    interprete=interpretation(lu);
    //Serial1.println(interprete);
    if(interprete!=0x0D){
      trans[tr]=interprete;
      tr--;
    }else{
      int a=1;
      tr=9-tr;
      for(int i=1;i<tr;i++)a*=10;
      for(int i=9;i>0;i--){
        com+=trans[i]*a;
        a/=10;
      }
      if(trans[10]==1)frequancePWM=com;
      if(trans[10]==2)pwm=com;
      Serial1.println(com);
      for(int i=0;i<10;i++)trans[i]=0;
      analogWriteFrequency(20,frequancePWM);
      analogWrite(20,pwm);
      tr=10;
      com=0;
    }
  }
}
