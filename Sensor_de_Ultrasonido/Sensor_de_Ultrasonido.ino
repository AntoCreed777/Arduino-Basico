const int trigger=13;
const int echo=3;
const int led=9;

void setup() {
  Serial.begin(9600);            //sincroniza la velocidad de transmision entre el COMPU y el ARDUINO
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(led,OUTPUT);
  digitalWrite(trigger,LOW);
}

void loop() {
  long t;
  long d;
  int brillo;

  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);

  t=pulseIn(echo,HIGH);
  d=t/59;

  Serial.print("Distancia: ");
  Serial.print(d);
  Serial.print("cm"); 
  Serial.println();
  delay(100);

  if(d<=10){
    brillo=255-(d*25.5);
    analogWrite(led,brillo);

  }
  


}
