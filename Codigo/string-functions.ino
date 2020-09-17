
//Código copiado do sketch "23-05-2016"
//Modificações:
  //* Mudança das funções - char/string

//********************************************************************************

//Inclusão de bibliotecas:
#include <SPI.h> //inclusão da lib SPI
#include <Ethernet.h> //inclusão da lib Ethernet
#include <DHT.h> //inclusão da lib umidade e temp

//Definiçôes DHT (serão usadas para inciar uma instância da lib DHT mais abaixo)
#define DHTPin A8 // pino em que o sensor será conectado (analógico 8)
#define DHType DHT11 // tipo do sensor DHT (DHT11)


// A linha abaixo define o MAC adress da Shield
byte mac[] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };


// Os valores abaixo definem o endereço IP, gateway e máscara.
// Configurada de acordo com a rede local onde o sistema será implantado.
IPAddress ip(192, 168, 2, 250);      //Define o endereço IP
IPAddress gateway(192, 168, 2, 1); //Define o gateway
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede


// Inicializa um servidor com o nome de "server"
EthernetServer server(80); // será iniciado na porta 80

// DECLARAÇÃO DE VARIÁVEIS DO PROJETO E MAPEAMENTO DE PORTAS:
int ledSalaEstar = 30;
int ledCozinha = 32;
int ledAreaServico = 34;
int ledGaragem = 36;
int ledSalaTV = 38;
int ledQuarto1 = 40;
int ledQuarto2 = 42;
int ledBanheiro = 44;
int ledFundo1 = 46;
int ledFundo2 = 48;
int ledFrente = 50;

int sensorChama = 6;
int sensorPresenca = 5;
int buzzer = 4;


//----------------------------------------------  DHT  ---------------------------------------------------------
  DHT sensorDHT(DHTPin, DHType); // cria uma instância da lib DHT com nome sensorDHT
//-------------------------------------------------------------------------------------------------------------


void setup()
{
// **********************************CONFIGURAÇÕES DE PINAGEM DE CADA VARIÁVEL*******************************************
  
  // todos os leds iniciam como saída de dados e estado inativo
  pinMode(ledSalaEstar, OUTPUT);
  digitalWrite(ledSalaEstar, LOW);
  
  pinMode(ledCozinha, OUTPUT);
  digitalWrite(ledCozinha, LOW);
  
  pinMode(ledAreaServico, OUTPUT);
  digitalWrite(ledAreaServico, LOW);
  
  pinMode(ledGaragem, OUTPUT);
  digitalWrite(ledGaragem, LOW);
  
  pinMode(ledSalaTV, OUTPUT);
  digitalWrite(ledSalaTV, LOW);
  
  pinMode(ledQuarto1, OUTPUT);
  digitalWrite(ledQuarto1, LOW);
  
  pinMode(ledQuarto2, OUTPUT);
  digitalWrite(ledQuarto2, LOW);
  
  pinMode(ledCozinha, OUTPUT);
  digitalWrite(ledCozinha, LOW);
  
  pinMode(ledBanheiro, OUTPUT);
  digitalWrite(ledBanheiro, LOW);
  
  pinMode(ledFundo1, OUTPUT);
  digitalWrite(ledFundo1, LOW);
  
  pinMode(ledFundo2, OUTPUT);
  digitalWrite(ledFundo2, LOW);
  
  pinMode(ledFrente, OUTPUT);
  digitalWrite(ledFrente, LOW);
  
  // todos os sensores iniciam como entrada de dados
  pinMode(sensorChama, INPUT);
  pinMode(sensorPresenca, INPUT);
  
  // o buzzer inicia como saída de dados
  pinMode(buzzer, OUTPUT);
  
//*****************************************************************************************************************************************************

//Inicializa a conexao ethernet e o servidor web (na porta 80, definida anteriormente)
  Ethernet.begin(mac, ip, gateway, subnet); //Inicializa a lib Ethernet com os valores de mac, ip, gateway e subnet definidos anteriormente
  server.begin(); // Inicializa o EthernetServer (definido anteriormente como "server")

sensorDHT.begin(); // incia essa instância



}

void loop()
{  
  digitalWrite(ledSalaEstar, HIGH);
  digitalWrite(ledCozinha, HIGH);
  ChamarPagina();
}



//*************************************DEFINIÇÃO DAS FUNÇÕES DO PROJETO*******************************************************

String EstadoDoLed (int led) // Função que retorna em string o estado de um led
{
  if (digitalRead(led) == HIGH){ // se o led estiger ligado
    return "Ligado"; // retorne a palavra "Ligado"
  }
  else { //se não
    return "Desligado"; // retorne a palavra "Desligado"
  }
  return "Laala"; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String EstadoChama () // Função que retorna em string o estado do sensor de chama
{
  if (digitalRead(sensorChama) != 1) // se a leitura do pino do sensor for diferente de 1
  {
    return "Fogo detectado!"; // retorne que o fogo foi detectado
  }
  else //se não
  {
    return "Tá de boa"; // retorne que não há fogo
  }
  return "nada";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String Umidade() // Função que retorna em texto a leitura da umidade por um sensor dht
{
  float UmidadeFloat = sensorDHT.readHumidity();// variável que armazena a leitura da umidade
  String UmidadeString = String(UmidadeFloat); // variável que converte a leitura para string
  return UmidadeString; // retorna em texto
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String Temperatura()// Função que retorna em char a leitura da temperatura por um sensor dht
{
  float TemperaturaFloat = sensorDHT.readTemperature();// variável que armazena a leitura da temperatura
  String TemperaturaString = String(TemperaturaFloat);// variável que converte a leitura para string
  return TemperaturaString;// retorna em texto
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
  client.print("Sensor de Presença: ");
  client.println();
  client.println("<br>");
  client.print("Umidade: ");
  client.println(Umidade());
  client.println("<br>");
  client.print("Temperatura: ");
  client.println(Temperatura());
  client.println("<br>");
  client.println("</p>");
      
  client.println("<h1>Estado dos Leds</h1>");
  
  client.println("<h3>Térreo</h3>");
  client.println("<p>");
  client.print("Sala de Estar: ");
  client.print(EstadoDoLed(ledSalaEstar));
  client.println("<br>");
  client.print("Cozinha: ");
  client.print(EstadoDoLed(ledCozinha));
  client.println("<br>");
  client.print("Área de Serviço: ");
  client.print(EstadoDoLed(ledAreaServico));
  client.println("<br>");
  client.print("Garagem: ");
  client.print(EstadoDoLed(ledGaragem));
  client.println("<br>");
  client.println("</p>");
      
  client.println("<h3>Primeiro Andar</h3>");
  client.println("<p>");
  client.print("Sala de TV: ");
  client.print(EstadoDoLed(ledSalaTV));
  client.println("<br>");
  client.print("Quarto 1: ");
  client.print(EstadoDoLed(ledQuarto1));
  client.println("<br>");
  client.print("Quarto 2: ");
  client.print(EstadoDoLed(ledQuarto2));
  client.println("<br>");
  client.print("Banheiro: ");
  client.print(EstadoDoLed(ledBanheiro));
  client.println("<br>");
  client.println("</p>");
      
  client.println("<h3>Jardim</h3>");
  client.println("<p>");
  client.print("Led 1: ");
  client.print(EstadoDoLed(ledFundo1));
  client.println("<br>");
  client.print("Led 2: ");
  client.print(EstadoDoLed(ledFundo2));
  client.println("<br>");
  client.print("Led 3: ");
  client.print(EstadoDoLed(ledFrente));
  client.println("<br>");
  client.println("</p>");
      
  client.println("</body>");
  client.println("</html>");

  delay(1);
  client.stop();
  }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
