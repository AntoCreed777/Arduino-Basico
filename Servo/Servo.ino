#include <Servo.h>
Servo servomotor;
int direccion1=0;
int direccion2=0;
int direccion3=0;

void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  servomotor.attach(9);
}

void loop() {
direccion1=digitalRead(2);
direccion2=digitalRead(3);
direccion3=digitalRead(4);

if(direccion1==1&&direccion2==0&&direccion3==0){
servomotor.write(0);
}

if(direccion1==0&&direccion2==1&&direccion3==0){
servomotor.write(90);
}

if(direccion1==0&&direccion2==0&&direccion3==1){
servomotor.write(180);
}


}
