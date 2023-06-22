#include <ESP8266WiFi.h>
#include <Ethernet.h>//libreria ethernet
#include <SPI.h>//libreria ethernet
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "dbenavid";
const char* password = "Dial-7681810";

String serverName = "http://pepa.desem.cl/antonio/update-sensor.php";

int hum, luz;//constantes para humedad
int sensorhumPIN=A5;
int sensorluzPIN=A4;

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0xEE}; // Direccion MAC
byte ip[] = { 192,168,1,109 }; // Direccion IP del Arduino
byte server[] = { 192,168,1,91 }; // Direccion IP del servidor192,168,0,14

DHT dht(DHTPIN, DHTTYPE);       //Definimos objeto tipo dht
EthernetClient cliente;         //objeto del ethernet

void setup() {
  Serial.begin(9600);           //Inicializamos comunicación serie
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  
  Ethernet.begin(mac, ip);      // Inicializamos el Ethernet Shield
}

void loop() {
  Serial.println("Leyendo datos");
  Serial.println("espere...");
  
  //codigo para la temperatura
  int hum = analogRead(sensorhumPIN);// Leemos la humedad
  int luz = analogRead(sensorluzPIN);// Leemos la luz
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
  String strhum = conversion(hum);
  String strluz= conversion(luz);
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
String conversion(int valor){
  String strvalor;
  strvalor += valor;
  return(strvalor);
    
    }
