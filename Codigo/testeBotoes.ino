#include <SPI.h>
#include <Ethernet.h>
 
int PinoLed1 = 36;
int PinoLed2 = 38;
int PinoLed3 = 40;
 
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };

IPAddress ip(192, 168, 1, 250);      //Define o endereço IP
IPAddress gateway(192, 168, 1, 1); //Define o gateway
IPAddress subnet(255, 255, 0, 0); //Define a máscara de rede
 
EthernetServer server(80);
 
void setup(){
  Ethernet.begin(mac, ip, gateway, subnet); //Inicializa a lib Ethernet com os valores de mac, ip, gateway e subnet definidos anteriormente
  server.begin(); // Inicializa o EthernetServer (definido anteriormente como "server")
  pinMode(PinoLed1, OUTPUT);
  pinMode(PinoLed2, OUTPUT);
  pinMode(PinoLed3, OUTPUT);
}
 
void loop(){
  char* params;



  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
  
 
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();

          client.print("<h1><a href='?led=000'>Servidor Web Embarcado</a></h1>");

          if (strcmp(params, "?led=100") == 0){
            digitalWrite(PinoLed1, HIGH);
            digitalWrite(PinoLed2, LOW);
            digitalWrite(PinoLed3, LOW);
            server.print("<a href='?led=000'><button style='border: 2px solid #00CD00;' type='button'><b>LED1 LIGADO</b></button></a>");
            server.print("<a href='?led=010'><button style='border: 2px solid #990000;' type='button'>LED2 DESLIGADO</button></a>");
            server.print("<a href='?led=001'><button style='border: 2px solid #990000;' type='button'>LED3 DESLIGADO</button></a>");
            }

          else if(strcmp(params, "?led=010") == 0){
            server.print("<a href='?led=100'><button style='border: 2px solid #990000;' type='button'>LED1 DESLIGADO</button></a>");
            server.print("<a href='?led=000'><button style='border: 2px solid #00CD00;' type='button'><b>LED2 LIGADO</b></button></a>");
            server.print("<a href='?led=001'><button style='border: 2px solid #990000;' type='button'>LED3 DESLIGADO</button></a>");
            digitalWrite(PinoLed1, LOW);
            digitalWrite(PinoLed2, HIGH);
            digitalWrite(PinoLed3, LOW);
          }

          else if(strcmp(params, "?led=010") == 0){
            server.print("<a href='?led=100'><button style='border: 2px solid #990000;' type='button'>LED1 DESLIGADO</button></a>");
            server.print("<a href='?led=000'><button style='border: 2px solid #00CD00;' type='button'><b>LED2 LIGADO</b></button></a>");
            server.print("<a href='?led=001'><button style='border: 2px solid #990000;' type='button'>LED3 DESLIGADO</button></a>");
            digitalWrite(PinoLed1, LOW);
            digitalWrite(PinoLed2, HIGH);
            digitalWrite(PinoLed3, LOW);
          }
  
          else if(strcmp(params, "?led=001") == 0){
            digitalWrite(PinoLed1, LOW);
            digitalWrite(PinoLed2, LOW);
            digitalWrite(PinoLed3, HIGH);
            server.print("<a href='?led=100'><button style='border: 2px solid #990000;' type='button'>LED1 DESLIGADO</button></a>");
            server.print("<a href='?led=010'><button style='border: 2px solid #990000;' type='button'>LED2 DESLIGADO</button></a>");
            server.print("<a href='?led=000'><button style='border: 2px solid #00CD00;' type='button'><b>LED3 LIGADO</b></button></a>");
          }

          else if(strcmp(params, "?led=000") == 0){
            digitalWrite(PinoLed1, LOW);
            digitalWrite(PinoLed2, LOW);
            digitalWrite(PinoLed3, LOW);
            server.print("<a href='?led=100'><button style='border: 2px solid #990000;' type='button'>LED1 DESLIGADO</button></a>");
            server.print("<a href='?led=010'><button style='border: 2px solid #990000;' type='button'>LED2 DESLIGADO</button></a>");
            server.print("<a href='?led=001'><button style='border: 2px solid #990000;' type='button'>LED3 DESLIGADO</button></a>");
          }
  
          delay(1);
          client.stop();
        
        }
      }
    }
  }
 } 
