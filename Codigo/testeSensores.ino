#include <DHT.h>

#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>

#include <SPI.h>

#define DHTPin A8
#define DHType DHT11

byte mac[] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };

IPAddress ip(192, 168, 0, 250);   
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(80); 

int led_1 = 3;
int led_2 = 4;


int sensorChama = 6;
  DHT sensorDHT(DHTPin, DHType);


void setup() {
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  
  digitalWrite(led_2, HIGH);
  digitalWrite(led_1, HIGH);

  pinMode(sensorChama, INPUT);

  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  sensorDHT.begin();

}

void loop() {
    
    ChamarPagina();
    MostrarNaSerial()
  
  }

char EstadoDoLed (int led) // Função que retorna em string o estado de um led
{
  if (digitalRead(led) == HIGH){ // se o led estiger ligado
    return 'Ligado'; // retorne a palavra "Ligado"
  }
  else { //se não
    return 'Desligado'; // retorne a palavra "Desligado"
  }
  return 'Laala'; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char EstadoChama () // Função que retorna em string o estado do sensor de chama
{
  if (digitalRead(sensorChama) != 1) // se a leitura do pino do sensor for diferente de 1
  {
    return 'Fogo detectado!'; // retorne que o fogo foi detectado
  }
  else //se não
  {
    return 'Tá de boa'; // retorne que não há fogo
  }
  return 'nada';
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char Umidade() // Função que retorna em char a leitura da umidade por um sensor dht
{
  float UmidadeFloat = sensorDHT.readHumidity();// variável que armazena a leitura da umidade
  char UmidadeChar = UmidadeFloat; // variável que converte a leitura para char
  return UmidadeChar; // retorna em texto
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char Temperatura()// Função que retorna em char a leitura da temperatura por um sensor dht
{
  float TemperaturaFloat = sensorDHT.readTemperature();// variável que armazena a leitura da temperatura
  char TemperaturaChar = TemperaturaFloat;// variável que converte a leitura para char
  return TemperaturaChar;// retorna em texto
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void ChamarPagina()
{
  //Cria um EthernetClient de nome "client" e atribui a ele a função available
  EthernetClient client = server.available();


//-------------------------------------- PÁGINA EM HTML  ------------------------------------------------
  client.println("<!DOCTYPE html>");
  client.println("<html>");
  
  client.println("<head>");
  client.println("<title>Automação Residencial</title>"); 
  client.println("<meta charset='utf-8' />");    
  client.println("</head>");

  
  client.println("<body>");
  client.println("<h1> Leitura dos Sensores </h1>");
  client.println("<p>"); 
  client.print("Sensor de Chama: ");
  client.print(EstadoChama());
  client.println("<br>");
  client.print("Umidade: ");
  client.println(Umidade());
  client.println("<br>");
  client.print("Temperatura: ");
  client.println(Temperatura());
  client.println("<br>");
  client.println("</p>");
      
  client.println("<h1>Estado dos Leds</h1>");
  client.println("<p>");
  client.print("Led 1: ");
  client.print(EstadoDoLed(led_1));
  client.println("<br>");
  client.print("Led 2: ");
  client.print(EstadoDoLed(led_2));
  client.println("<br>");
  
      
  client.println("</body>");
  client.println("</html>");

  delay(1);
  client.stop();
  }

void MostrarNaSerial()
{
   Serial.begin(9600);
 Serial.println("************************************* TESTE *****************************************");
 Serial.println(""); 
 Serial.println("SENSORES:");
 Serial.print("Umidade: ");
 Serial.println(Umidade());
 Serial.print("Temperatura: ");
 Serial.println(Temperatura());
 Serial.print("Chama: ");
 Serial.println(EstadoChama());
 Serial.println("");
 Serial.println("ESTADO DOS LEDS:");
 Serial.print("Led 1: ");
 Serial.println(EstadoDoLed(led_1));
 Serial.print("Led 2: ");
 Serial.println(EstadoDoLed(led_2));
}

