int x=5000;
int y=500;
int boton=4;
int estado=0;


void setup() {
pinMode(8,OUTPUT);  //Verde
pinMode(9,OUTPUT);  //Amarillo
pinMode(10,OUTPUT);  //Rojo
pinMode(boton,INPUT);
}

void loop() {
estado=digitalRead(boton);

if(estado==HIGH){



  digitalWrite(8,HIGH);
  delay(x);
  digitalWrite(8,LOW);



  digitalWrite(9,HIGH);
  delay(y);
  digitalWrite(9,LOW);
  delay(y);
  digitalWrite(9,HIGH);
  delay(y);
  digitalWrite(9,LOW);
  delay(y);
  digitalWrite(9,HIGH);
  delay(y);
  digitalWrite(9,LOW);



  digitalWrite(10,HIGH);
  delay(x);
  digitalWrite(10,LOW);




}
else{}

}
