#include <ESP8266WiFi.h>
#include <Ethernet.h>//libreria ethernet
#include <SPI.h>//libreria ethernet
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

const char* ssid = "dbenavid";
const char* password = "Dial-7681810";

byte mac_addr[] = {0xDE};           //0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED

IPAddress server_addr(177,221,140,242);  // IP of the MySQL *server* here
char user[] = "ravencl_AntoCreed777";              // MySQL user login username
char clave[] = "ant.MYSQL";        // MySQL user login password

EthernetClient client;                                //objeto del ethernet

MySQL_Connection conn((Client *)&client);

int temp,hum;

void setup() {
  Serial.begin(9600);
  delay(3000);
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


  Ethernet.begin(mac_addr);
  if (conn.connect(server_addr, 3306, user, clave)) {
    delay(1000);
  }
  else
    Serial.println("Connection failed.");
}

void loop() {
  Serial.println("Envio de dato, conectando...");
  Serial.println("Envio de datos");
  Serial.println("Conectando...");
  if (client.connect(server_addr, 80)>0) {  // Conexion con el servidor(client.connect(server, 80)>0
    client.print("GET /arduino/control/conexion_arduino.php?hum_php="); // Enviamos los datos por GET
    client.print(hum);
    client.print("&temp_php=");
    client.print(temp);
    client.println(" HTTP/1.0");
    client.println("User-Agent: Arduino 1.0");
    client.println();
    Serial.println("Envio con exito");
    delay(1000);
  } else {
    Serial.println("Fallo en la conexion");
    delay(2000);
  }
  if (!client.connected()) {
    Serial.println("Desconectando");
    delay(1000);
  }
  client.stop();
  client.flush();

}
