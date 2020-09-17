//Código copiado de 29-05-2016Funcional
//Modificações:
  //** Tentativa de implementação de botões (Baseado no sketch Tetse)
  //** Início: junho, 8 (19:30);
  //** 

//********************************************************************************

//Inclusão de bibliotecas:
#include <SPI.h> //inclusão da lib SPI
#include <Ethernet.h> //inclusão da lib Ethernet
#include <DHT.h> //inclusão da lib umidade e temp

//Definiçôes DHT (serão usadas para setar o sensor DHT mais abaixo)
#define DHTPin A1 // pino em que o sensor será conectado (analógico 8)
#define DHType DHT11 // tipo do sensor DHT (DHT11)


// A linha abaixo define o MAC adress da Shield
byte mac[] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };


// Os valores abaixo definem o endereço IP, gateway e máscara.
// Configurada de acordo com a rede local onde o sistema será implantado.
IPAddress ip(192, 168, 1, 235);      //Define o endereço IP
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede


// Inicializa um servidor com o nome de "server"
EthernetServer server(80); // será iniciado na porta 80

// DECLARAÇÃO DE VARIÁVEIS DO PROJETO E MAPEAMENTO DE PORTAS:
const int ledSalaEstar = 2;
const int ledCozinha = 3;
const int ledAreaServico = 34;
const int ledGaragem = 32;
const int ledSalaTV = 38;
const int ledQuarto1 = 40;
const int ledQuarto2 = 42;
const int ledBanheiro = 44;
const int ledFundo1 = 46;
const int ledFundo2 = 48;
const int ledFrente = 50;


const int sensorChama = 5;
const int sensorPresenca = 6;
const int buzzer = 7;

String readString;

                //*********************************
                /**/boolean alarmeOnOff = true;//*    <--- LIGUE/DESLIGUE O ALARME AQUI
                //*********************************

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
  Ethernet.begin(mac, ip, subnet); //Inicializa a lib Ethernet com os valores de mac, ip, gateway e subnet definidos anteriormente
  server.begin(); // Inicializa o EthernetServer (definido anteriormente como "server")

  sensorDHT.begin(); // incia essa instância



}


//******************************loop*******************************************

void loop()
{  
    Alarme(buzzer,sensorPresenca);

  ChamarPagina();
}



//*************************************DEFINIÇÃO DAS FUNÇÕES DO PROJETO*******************************************************




////////////////////////////////////////////ESTADO DO LED//////////////////////////////////
String EstadoDoLed (int inled) // Função que retorna em string o estado de um led
{
  String resposta; 
  if(digitalRead(inled)==HIGH){
    resposta = "<font color=#00ff00><strong> LIGADO </strong></font> "; 
    return resposta;
  } else {
    resposta = "<font color=#ff0000><strong> DESLIGADO </strong></font> ";
    return resposta;
  }
  
}

//////////////////////////////////////////////////  ALARME //////////////////////////////////////////////////////////////////////////////
void Alarme(int buzz, int sensor)
{
  if(alarmeOnOff == true){
    if  (digitalRead(sensor) == 1)
    {
      digitalWrite(buzz, HIGH);
    }
    else
    {
      digitalWrite(buzz, LOW);
    } 
  }

  else{ 
    }
}


///////////////////////////////////////ESTADO CHAMA////////////////////////////////////////////////////

String EstadoChama() // Função que retorna em string o estado do sensor de chama
{
  int estado = digitalRead(sensorChama);
  String resposta;
  if (estado == 1) // se a leitura do pino do sensor for diferente de 1
  {
    resposta = "<font color=#3366cc><strong> SEM PERIGO </strong></font> ";
    return resposta;// retorne que o fogo foi detectado
  }
  else //se não
  {
    resposta = "<font color=#ff0000><strong>  CALL 911 - EMERGÊNCIA - OH GOD </strong></font> ";
    return resposta; // retorne que não há fogo
  }
  return resposta = "Não detectado, favor verificar sensor."; 
}


//////////////////////////////////////CHAMA A PAGINA///////////////////////////////////////////////////////
void ChamarPagina()
{
  //Cria um EthernetClient de nome "client" e atribui a ele a função available
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
          client.println(sensorDHT.readHumidity());
          client.println("% <br>");
          client.print("Temperatura: ");
          client.println(sensorDHT.readTemperature());
          client.println(" *C <br>");
          client.println("</p>");
        
          client.println("<h1>Estado dos Leds</h1>");
          
          client.println("<h3>Térreo</h3>");
          client.println("<p>");
          client.print("Sala de Estar: ");
          client.print(EstadoDoLed(ledSalaEstar));
          
          client.println("<a href=\"/?ledon\"\">Ligar o led</a>");
          client.println("<a href=\"/?ledoff\"\">Desligar o led</a><br />");

          
          
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
          //client.print("Led 3: ");
          //client.print(EstadoDoLed(ledFrente));
          client.println("<br>");
          client.println("</p>");
              
          client.println("</body>");
          client.println("</html>");   
           
           
          delay(1);
          client.stop();

          
          if(readString.indexOf("?ledon") > 0)
          {
            digitalWrite(ledSalaEstar, HIGH);
          }
          else {
            if(readString.indexOf("?ledoff") > 0)
            {
              digitalWrite(ledSalaEstar, LOW);
            }
          }
          readString="";     
             
        }
      }
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
