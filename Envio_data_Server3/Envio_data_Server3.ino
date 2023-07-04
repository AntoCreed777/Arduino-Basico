#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "S91 Pro";
const char* password = "ant.WIFI";

String serverName = "http://pepa.desem.cl/antonio/update-sensor.php";
//Variables MUX
const int muxSIG = A0;
const int muxS0 = D2;
const int muxS1 = D3;
const int muxS2 = D4;
const int muxS3 = D5;

void SetMuxChannel(byte channel)
{
  digitalWrite(muxS0, bitRead(channel, 0));
  digitalWrite(muxS1, bitRead(channel, 1));
  digitalWrite(muxS2, bitRead(channel, 2));
  digitalWrite(muxS3, bitRead(channel, 3));
}

//Pines Sensores
const int PinHum=0 ;
const int PinLuz=1 ;

void setup() {
  Serial.begin(9600);           //Inicializamos comunicación serie
  WiFi.begin(ssid, password);
  
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);
  pinMode(muxS2, OUTPUT);
  pinMode(muxS3, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("--------------------");
  //Lectura sensor Humedad
  SetMuxChannel(PinHum);
  int hum=analogRead(muxSIG);
  int conversionhum=map(hum,1023,0,0,100);
  /////////////////////////////////////////////////////
  //Lectura sensor Luz
  SetMuxChannel(PinLuz);
  int luz=analogRead(muxSIG);
  luz=constrain(luz,0,100);
  
  Serial.print("Humedad: ");
  Serial.print(conversionhum);
  Serial.println("%");
  Serial.print("Luz: ");
  Serial.print(luz);
  Serial.println("%");
  delay(2000);

  WiFiClient client;
  HTTPClient http;
  String strhum = String(conversionhum);
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
