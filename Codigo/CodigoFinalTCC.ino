
//--------------CÓDIGO FINAL - TCC AUTOMAÇÃO RESIDENCIAL------------------
//********************************************************************************
// INICIADO: 18/05 - Bia e Andreza (copiamos e colamos aqui os códigos que já estavam prontos <VARS> )
// incrementado: 20/05 - Andreza
  // *Definição da base da página em html
  // *Função que retorna o estado do led (em texto) criada
  // *Definição das variavei .ç s (char) de exibição estado de cada led
  // *EXIBIÇÃO DO STATUS DE CADA LED NA PAGINA FINALIZADA - 21/05 (2:17am)
//incrementado: 21/05 - Andreza
  // *Função que retorna o estado do sensor de chama criada
  // *Definição da variável de estado do sensor de chama
  // *EXIBIÇÃO DO STATUS DO SENSOR DE CHAMA NA PÁGINA FINALIZADA (22:38)
//incrementado: 22/05 - Andreza
  // *Inclusão da Lib DHT, definições e instância finalizadas
  // *sensorDHT inicializado
  // *Definição das variáveis de exibição da umidade e da temperatura
  // *Criação das funções de exibição da  umidade e da temperatura
  //*EXIBIÇÃO DOS VALORES DE UMIDADE E TEMPERATURA NA PÁGINA FINALIZADA (18:46)

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

// O sensor DHT não foi esquecido, ele é referenciado mais abaixo (no loop), como uma instância da lib dht

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
  
}

void loop()
{ 
  //Cria um EthernetClient de nome "client" e atribui a ele a função available
  EthernetClient client = server.available();
  
//----------------------------------------------  DHT  ---------------------------------------------------------
  DHT sensorDHT(DHTPin, DHType); // cria uma instância da lib DHT com nome sensorDHT
  sensorDHT.begin(); // incia essa instância
//-------------------------------------------------------------------------------------------------------------
  
  //DECLARAÇÃO DE VARIÁVEIS DE EXIBIÇÃO DE ESTADO DE CADA LED
  char EstLedSalaEstar = EstadoDoLed(ledSalaEstar); //armazena o retorno da função 'EstadoDoLed' apliacada ao led da Sala de Estar
  char EstLedCozinha = EstadoDoLed(ledCozinha); //armazena o retorno da função 'EstadoDoLed' apliacada ao led da Cozinha
  char EstLedAreaServico = EstadoDoLed(ledAreaServico); //armazena o retorno da função 'EstadoDoLed' apliacada ao led da Area de Servico
  char EstLedGaragem = EstadoDoLed(ledGaragem); //armazena o retorno da função 'EstadoDoLed' apliacada ao led da Garagem
  char EstLedSalaTV = EstadoDoLed(ledSalaTV); //armazena o retorno da função 'EstadoDoLed' apliacada ao led da Sala de TV
  char EstLedQuarto1 = EstadoDoLed(ledQuarto1); //armazena o retorno da função 'EstadoDoLed' apliacada ao led do Quarto 1
  char EstLedQuarto2 = EstadoDoLed(ledQuarto2); //armazena o retorno da função 'EstadoDoLed' apliacada ao led do Quarto 2
  char EstLedBanheiro = EstadoDoLed(ledBanheiro); //armazena o retorno da função 'EstadoDoLed' apliacada ao led do Banheiro
  char EstLedFundo1 = EstadoDoLed(ledFundo1); //armazena o retorno da função 'EstadoDoLed' apliacada ao led 1 do Jardim
  char EstLedFundo2 = EstadoDoLed(ledFundo2); //armazena o retorno da função 'EstadoDoLed' apliacada ao led 2 do Jardim
  char EstLedFrente = EstadoDoLed(ledFrente); //armazena o retorno da função 'EstadoDoLed' apliacada ao led 3 do Jardim
  
  //DECLARAÇÃO DE VARIÁVEIS DE EXIBIÇÃO DOS SENSORES
  char EstSensorChama = EstadoChama(sensorChama); // armazena o retorno da função 'EstadoChama' aplicada ao sensor de chama
  char EstUmidade = Umidade(sensorDHT); // armazena o retorno da função 'Umidade' aplicada ao sensor DHT
  char EstTemperatura = Temperatura (sensorDHT); // armazena o retorno da função 'Temperatura' aplicada ao sensor DHT
  

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
  client.print(EstSensorChama);
  client.println("<br>");
  client.print("Sensor de Presença: ");
  client.println();
  client.println("<br>");
  client.print("Umidade: ");
  client.println(EstUmidade);
  client.println("<br>");
  client.print("Temperatura: ");
  client.println(EstTemperatura);
  client.println("<br>");
  client.println("</p>");
  		
  client.println("<h1>Estado dos Leds</h1>");
  
  client.println("<h3>Térreo</h3>");
  client.println("<p>");
  client.print("Sala de Estar: ");
  client.print(EstLedSalaEstar);
  client.println("<br>");
  client.print("Cozinha: ");
  client.print(EstLedCozinha);
  client.println("<br>");
  client.print("Área de Serviço: ");
  client.print(EstLedAreaServico);
  client.println("<br>");
  client.print("Garagem: ");
  client.print(EstLedGaragem);
  client.println("<br>");
  client.println("</p>");
  		
  client.println("<h3>Primeiro Andar</h3>");
  client.println("<p>");
  client.print("Sala de TV: ");
  client.print(EstLedSalaTV);
  client.println("<br>");
  client.print("Quarto 1: ");
  client.print(EstLedQuarto1);
  client.println("<br>");
  client.print("Quarto 2: ");
  client.print(EstLedQuarto2);
  client.println("<br>");
  client.print("Banheiro: ");
  client.print(EstLedBanheiro);
  client.println("<br>");
  client.println("</p>");
  		
  client.println("<h3>Jardim</h3>");
  client.println("<p>");
  client.print("Led 1: ");
  client.print(EstLedFundo1);
  client.println("<br>");
  client.print("Led 2: ");
  client.print(EstLedFundo2);
  client.println("<br>");
  client.print("Led 3: ");
  client.print(EstLedFrente);
  client.println("<br>");
  client.println("</p>");
  		
  client.println("</body>");
  client.println("</html>"); 
}


//*************************************DEFINIÇÕES DAS FUNÇÕES DO PROJETO*******************************************************
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char EstadoDoLed (int led) // Função que retorna em string o estado de um led
{
  if (digitalRead(led) == HIGH){ // se o led estiger ligado
    return 'Ligado'; // retorne a palavra "Ligado"
  }
  else { //se não
    return 'Desligado'; // retorne a palavra "Desligado"
  } 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char EstadoChama (int sensor) // Função que retorna em string o estado do sensor de chama
{
  if (digitalRead(sensor) != 1) // se a leitura do pino do sensor for diferente de 1
  {
    return 'Fogo detectado!'; // retorne que o fogo foi detectado
  }
  else //se não
  {
    return 'Tá de boa'; // retorne que não há fogo
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char Umidade(DHT sensor) // Função que retorna em char a leitura da umidade por um sensor dht
{
  float UmidadeFloat = sensor.readHumidity();// variável que armazena a leitura da umidade
  char UmidadeChar = UmidadeFloat; // variável que converte a leitura para char
  return UmidadeChar; // retorna em texto
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char Temperatura(DHT sensor)// Função que retorna em char a leitura da temperatura por um sensor dht
{
  float TemperaturaFloat = sensor.readTemperature();// variável que armazena a leitura da temperatura
  char TemperaturaChar = TemperaturaFloat;// variável que converte a leitura para char
  return TemperaturaChar;// retorna em texto
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
