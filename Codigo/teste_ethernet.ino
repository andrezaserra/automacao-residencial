#include <SPI.h>
#include <Ethernet.h>
  
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };

IPAddress ip(192, 168, 1, 250);      //Define o endereço IP
IPAddress gateway(192, 168, 1, 1); //Define o gateway
IPAddress subnet(255, 255, 0, 0); //Define a máscara de rede
     
EthernetServer server(80);
  
String readString;
const int Pin = 38;
const int Pin2 = 40;
  
void setup(){
  
  pinMode(Pin, OUTPUT);
  Ethernet.begin(mac, ip, gateway, subnet); //Inicializa a lib Ethernet com os valores de mac, ip, gateway e subnet definidos anteriormente
  server.begin(); // Inicializa o EthernetServer (definido anteriormente como "server")
}
  
void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
  
        if (readString.length() < 100) {
          readString += c;             
        }
 
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
           
          client.println("<HTML>");
          client.println("<BODY>");
          client.println("<H1>Acende LED</H1>");
          client.println("<hr />");
          client.println("<br />");
           
          client.println("<a href=\"/?ledon\"\">Ligar o led quarto rosa</a>");
          client.println("<br>");
          client.println("<a href=\"/?ledoff\"\">Desligar o led quarto rosa</a><br />");

          client.println("<br>");
          client.println("<a href=\"/?led2on\"\">Ligar o led quarto azul</a>");
          client.println("<br>");
          client.println("<a href=\"/?led2off\"\">Desligar o led quarto azul</a><br />");

          client.println("</BODY>");
          client.println("</HTML>");

          if(readString.indexOf("?ledon") > 0)
          {
            digitalWrite(Pin, HIGH);
          }
          else {
              if(readString.indexOf("?ledoff") > 0)
              {
                digitalWrite(Pin, LOW);
              }
              if(readString.indexOf("?led2on") > 0)
              {
              digitalWrite(Pin2, HIGH);
            }
            else {
              if(readString.indexOf("?led2off") > 0)
              {
                digitalWrite(Pin2, LOW);
              }
             }
           
           }
           
          delay(1);
          client.stop();
           
          readString="";    
        }
      }
    }
  }
 } 




