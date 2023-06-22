#include <ESP8266WiFi.h>
#include <Ethernet.h>//libreria ethernet
#include <SPI.h>//libreria ethernet

const char* ssid = "dbenavid";
const char* password = "Dial-7681810";

WiFiServer server(80);

// Configuracion del Ethernet Shield
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0xEE};     // Direccion MAC
byte ip[] = { 192,168,1,109 };                         // Direccion IP del Arduino
byte server[] = { 177,221,140,242 };                   // Direccion IP del servidor 177.221.140.242

EthernetClient cliente;                                //objeto del ethernet

void setup() {
  Serial.begin(9600);
  delay(3000);

  Ethernet.begin(mac, ip);                             // Inicializamos el Ethernet Shield
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
                                                    // Inicia el server
  server.begin();
  Serial.println("Server started");
 
                                                    // Imprime la dirección IP
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  Serial.println("Envio de dato, conectando...");
  Serial.println("Envio de datos");
  Serial.println("Conectando...");
  if (cliente.connect(server, 80)>0) {  // Conexion con el servidor(client.connect(server, 80)>0
    cliente.print("GET /arduino/control/conexion_arduino.php?pre_php="); // Enviamos los datos por GET
    cliente.print(P,2);
    cliente.print("&hum_php=");
    cliente.print(hum);
    cliente.print("&temp_php=");
    cliente.print(temp);
    cliente.println(" HTTP/1.0");
    cliente.println("User-Agent: Arduino 1.0");
    cliente.println();
    Serial.println("Envio con exito");
    delay(1000);
  } else {
    Serial.println("Fallo en la conexion");
    delay(2000);
  }
  if (!cliente.connected()) {
    Serial.println("Desconectando");
    delay(1000);
  }
  cliente.stop();
  cliente.flush();

}
