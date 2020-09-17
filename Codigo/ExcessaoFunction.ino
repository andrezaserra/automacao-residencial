#include <SPI.h> //inclusão da lib SPI
#include <Ethernet.h> //inclusão da lib Ethernet

byte mac[] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };

IPAddress ip(192, 168, 1, 235);      //Define o endereço IP
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede

EthernetServer server(80); // será iniciado na porta 80

// DECLARAÇÃO DE VARIÁVEIS DO PROJETO E MAPEAMENTO DE PORTAS:
const int led1 = 7;
const int led2 = 6;
const int led3 = 5;

String readString;


void setup() {
  
  pinMode(led1, OUTPUT);
  digitalWrite(led1, HIGH);

  pinMode(led2, OUTPUT);
  digitalWrite(led2, HIGH);

  pinMode(led3, OUTPUT);
  digitalWrite(led3, HIGH);

  Ethernet.begin(mac, ip, subnet); 
  server.begin(); 
  
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        if (readString.length() < 100) {
          readString += c;
        }

        if (c == '\n') {
          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<meta charset = 'utf-8' />");
          client.println("<meta http-equiv=\"refresh\" content=\"10\">");

          client.println("<head>");
          client.println("<title>Automação Residencial</title>");
          client.println("</head>");

          client.print("Led 1 ");
          client.println("<a href=\"/ ?leda1 \"/ >Ligar o led</a>");
          client.println("<a href=\"/ ?leda0 \"/ >Desligar o led</a><br/>");

          
          client.println("<br>");
          client.print("Led 2 ");
          client.println("<a href=\"/ ?ledb1 \"/ >Ligar o led</a>");
          client.println("<a href=\"/ ?ledb0 \"/ >Desligar o led</a><br/>");

          client.println("<br>");
          client.print("Led 3 ");
          client.println("<a href=\"/ ?ledc1 \"/ >Ligar o led</a>");
          client.println("<a href=\"/ ?ledc0 \"/ >Desligar o led</a><br/>");

          
          client.println("<br>");
          client.println("</body>");
          client.println("</html>");


          delay(10);
          client.stop();

          Ifs();

        }
      }
    }
  }
  }


 void Ifs()
  {
          if(readString.indexOf("?leda1") > 0)
          {
            digitalWrite(led1, HIGH);
          }

          else if (readString.indexOf("?leda0") > 0){
              digitalWrite(led1, LOW);
            }
            
          else if (readString.indexOf("?ledb1") > 0){
              digitalWrite(led2, HIGH);
            }

          else if (readString.indexOf("?ledb0") > 0){
              digitalWrite(led2, LOW);
            }
         
          else if (readString.indexOf("?ledc0") > 0){
              digitalWrite(led3, LOW);
            }

          else if (readString.indexOf("?ledc1") > 0){
              digitalWrite(led3, HIGH);
            }
          

          readString = "";


  }

