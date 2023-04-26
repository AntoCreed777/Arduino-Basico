int led1=3;
int led2=5;
int led3=6;
int ldr;
int conversion;


void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  ldr=analogRead(1);
  ldr=constrain(ldr,0,100);
  conversion=map(ldr,0,100,255,0);
  analogWrite(led1,conversion);
  analogWrite(led2,conversion);
  analogWrite(led3,conversion);
  Serial.println(conversion);
  delay(30);

}
