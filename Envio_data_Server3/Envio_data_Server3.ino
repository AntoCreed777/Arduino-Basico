#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "S91 Pro";
const char* password = "ant.WIFI";

String serverName = "http://pepa.desem.cl/antonio/update-sensor.php";

void setup() {
  Serial.begin(9600);           //Inicializamos comunicación serie
  WiFi.begin(ssid, password);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(A0,INPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("Leyendo datos");
  Serial.println("espere...");
  
  digitalWrite(D6,HIGH);
  delay(500);
  int hum = analogRead(A0);// Leemos la humedad
  delay(500);
  digitalWrite(D6,LOW);
  /////////////////////////////////////////////////////
  digitalWrite(D7,HIGH);
  delay(500);
  int luz = analogRead(A0);// Leemos la luz
  delay(500);
  digitalWrite(D7,LOW);
  
  luz=constrain(luz,0,100);
  luz=map(luz,0,100,100,0);
  
  Serial.print("Humedad: ");
  Serial.print(hum);
  Serial.println("%");
  Serial.print("Luz: ");
  Serial.print(luz);
  Serial.println("%");
  delay(2000);

  WiFiClient client;
  HTTPClient http;
  String strhum = String(hum);
  String strluz= String(luz);
  String serverPath = serverName+"?hum="+strhum+"&luz="+strluz;
  
  http.begin(client, serverPath.c_str());

  int httpResponseCode = http.GET();

  if (httpResponseCode >0) {
    if (http.getString() == "OK" ){
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
    }
    else
    {
        Serial.println(http.getString());
    }
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  
  delay(5000);
  
}
