//função estado alarme


#include <SPI.h> //inclusão da lib SPI
#include <Ethernet.h> //inclusão da lib Ethernet
#include <DHT.h> //inclusão da lib umidade e temp

//Definiçôes DHT (serão usadas para setar o sensor DHT mais abaixo)
#define DHTPin A8 // pino em que o sensor será conectado (analógico 8)
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
const int ledSalaEstar = 30;
const int ledCozinha = 32;
//const int ledAreaServico = 34;
const int ledGaragem = 34;
const int ledSalaTV = 36;
const int ledQuarto1 = 38;
const int ledQuarto2 = 40;
const int ledBanheiro = 42;
const int ledFundo1 = 44;
const int ledFundo2 = 46;
const int ledFrente = 48;

const int sensorLuminosidade = A9;
const int sensorChama = 6;
const int sensorPresenca = 5;
const int buzzer = 4;

String readString;

//*********************************
/**/boolean alarmeOnOff = false;//*  
//*********************************

//----------------------------------------------  DHT  ---------------------------------------------------------
DHT sensorDHT(DHTPin, DHType); // cria uma instância da lib DHT com nome sensorDHT
//-------------------------------------------------------------------------------------------------------------


void setup()
{
  // **********************************CONFIGURAÇÕES DE PINAGEM DE CADA VARIÁVEL*******************************************

  // todos os leds iniciam como saída de dados e estado inativo
  pinMode(ledSalaEstar, OUTPUT);
  digitalWrite(ledSalaEstar, HIGH);

  pinMode(ledCozinha, OUTPUT);
  digitalWrite(ledCozinha, HIGH);

/*  pinMode(ledAreaServico, OUTPUT);
  digitalWrite(ledAreaServico, HIGH);*/

  pinMode(ledGaragem, OUTPUT);
  digitalWrite(ledGaragem, LOW);

  pinMode(ledSalaTV, OUTPUT);
  digitalWrite(ledSalaTV, LOW);

  pinMode(ledQuarto1, OUTPUT);
  digitalWrite(ledQuarto1, LOW);

  pinMode(ledQuarto2, OUTPUT);
  digitalWrite(ledQuarto2, LOW);

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
  pinMode(sensorLuminosidade, INPUT);

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
  
  Alarme(buzzer, sensorPresenca);
  Jardim();
  
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
          client.println("<meta http-equiv=\"refresh\" content=\"6\">");

          client.println("<head>");
          client.println("<title>Automação Residencial</title>");
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

          client.println("<h3>ALARME</h3>");
          client.print(EstadoDoAlarme(alarmeOnOff));
          client.println("<br>");
          client.println("<a href=\"/ ?alarmon \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a>");
          client.println("<a href=\"/ ?alarmoff \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>");

          client.println("<h1>Estado dos Leds</h1>");

          client.println("<h3>Térreo</h3>");
          client.println("<p>");
          client.print("Sala de Estar: ");
          client.print(EstadoDoLed(ledSalaEstar));
          client.println("<br>");
          client.println("<a href=\"/ ?leda1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a>");
          client.println("<a href=\"/ ?leda0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>");

          
          client.println("<br>");
          client.print("Cozinha: ");
          client.print(EstadoDoLed(ledCozinha));
          client.println("<br>");
          client.println("<a href=\"/ ?ledb1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>");
          client.println("<a href=\"/ ?ledb0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>");
          
          
         /* client.println("<br>");
          client.print("Área de Serviço: ");
          client.print(EstadoDoLed(ledAreaServico));
          client.println("<a href=\"/ ?ledc1 \"/ >Ligar</a>");
          client.println("<a href=\"/ ?ledc0 \"/ >Desligar</a><br/>"); */
          
          
          client.println("<br>");
          client.print("Garagem: ");
          client.print(EstadoDoLed(ledGaragem));
          client.println("<br>");
          client.println("<a href=\"/ ?ledc1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>");
          client.println("<a href=\"/ ?ledc0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>");
          client.println("<br>");
          client.println("</p>");

          client.println("<h3>Primeiro Andar</h3>");
          client.println("<p>");
          client.print("Sala de TV: ");
          client.print(EstadoDoLed(ledSalaTV));
          client.println("<br>");
          client.println("<a href=\"/ ?ledd1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>");
          client.println("<a href=\"/ ?ledd0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>");


          
          client.println("<br>");
          client.print("Quarto 1: ");
          client.print(EstadoDoLed(ledQuarto1));
          client.println("<br>");
          client.println("<a href=\"/ ?lede1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>");
          client.println("<a href=\"/ ?lede0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>");

          
          client.println("<br>");
          client.print("Quarto 2: ");
          client.print(EstadoDoLed(ledQuarto2));
          client.println("<br>");
          client.println("<a href=\"/ ?ledf1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>");
          client.println("<a href=\"/ ?ledf0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>");

          
          client.println("<br>");
          client.print("Banheiro: ");
          client.print(EstadoDoLed(ledBanheiro));
          client.println("<br>");
          client.println("<a href=\"/ ?ledg1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>");
          client.println("<a href=\"/ ?ledg0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>");

          
          client.println("<br>");
          client.println("</p>");
          client.println("<h3>Jardim</h3>");
          client.print(EstadoDoLed(ledFrente));
          client.println("<br>");
          client.println("<a href=\"/ ?ledh1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>");
          client.println("<a href=\"/ ?ledh0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>");
          
          
          client.println("<br>");
          client.println("</body>");
          client.println("</html>");
          delay(10);
          client.stop();

          IfsButtons();
          
        }
      }
    }
  }

}



//*************************************DEFINIÇÃO DAS FUNÇÕES DO PROJETO*******************************************************

////////////////////////////////////////////ESTADO DO LED//////////////////////////////////
String EstadoDoLed (int inled) // Função que retorna em string o estado de um led
{
  String resposta;
  if (digitalRead(inled) == HIGH) {
    resposta = "<font color=#00ff00><strong> LIGADO </strong></font> ";
    return resposta;
  } else {
    resposta = "<font color=#ff0000><strong> DESLIGADO </strong></font> ";
    return resposta;
  }

}


///////////////////////////////ESTADO ALARME////////////////////////////////////////////

String EstadoDoAlarme (bool estado) // Função que retorna em string o estado de um led
{
  String resposta;
  if (estado == true) {
    resposta = "<font color=#00ff00><strong> LIGADO </strong></font> ";
    return resposta;
  } else {
    resposta = "<font color=#ff0000><strong> DESLIGADO </strong></font> ";
    return resposta;
  }

}

//////////////////////////////////////////////////  ALARME //////////////////////////////////////////////////////////////////////////////
void Alarme(int buzz, int sensor) // Essa função tem como argumentos o buzzer e o sensor de presença (responsáveis pelo alarme da casa)
{
  if (alarmeOnOff == true) { // Se o alarme estiver ligado 
    if  (digitalRead(sensor) == 1) //
    {
      digitalWrite(buzz, HIGH);
    }
    else
    {
      digitalWrite(buzz, LOW);
    }
  }

  else {
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



///////////////////////////////////////JARDIM/////////////////////////////////////////////////////
void Jardim()
{
  int estado = analogRead(sensorLuminosidade);  //Lê o valor fornecido pelo LDR   
  // Caso o valor lido na porta analógica seja maior do que 
  if (estado > 800) // 800, os leds do jardim são acesos    
  {  
    digitalWrite(ledFundo1, HIGH); 
    digitalWrite(ledFundo2, HIGH); 
    digitalWrite(ledFrente, HIGH); 
  }  
  else  //Caso contrário, os leds são apagados  
  {  
    digitalWrite(ledFundo1, LOW); 
    digitalWrite(ledFundo2, LOW); 
    digitalWrite(ledFrente, LOW); 
  }  
}


void IfsButtons()
{
          if(readString.indexOf("?leda1") > 0)
          {
            digitalWrite(ledSalaEstar, HIGH);
          }

          else if (readString.indexOf("?leda0") > 0){//a
              digitalWrite(ledSalaEstar, LOW);
            }
            
          else if (readString.indexOf("?ledb1") > 0){//b
              digitalWrite(ledCozinha, HIGH);
            }

          else if (readString.indexOf("?ledb0") > 0){
              digitalWrite(ledCozinha, LOW);
            }
         
          else if (readString.indexOf("?ledc0") > 0){//c
              digitalWrite(ledGaragem, LOW);
            }

          else if (readString.indexOf("?ledc1") > 0){
              digitalWrite(ledGaragem, HIGH);
            }

          else if (readString.indexOf("?ledd0") > 0){//d
              digitalWrite(ledSalaTV, LOW);
            }

          else if (readString.indexOf("?ledd1") > 0){
              digitalWrite(ledSalaTV, HIGH);
            }

          else if (readString.indexOf("?lede0") > 0){//e
              digitalWrite(ledQuarto1, LOW);
            }

          else if (readString.indexOf("?lede1") > 0){
              digitalWrite(ledQuarto1, HIGH);
            }

          else if (readString.indexOf("?ledf0") > 0){//f
              digitalWrite(ledQuarto2, LOW);
            }

          else if (readString.indexOf("?ledf1") > 0){
              digitalWrite(ledQuarto2, HIGH);
            }          

          else if (readString.indexOf("?ledg0") > 0){//g
              digitalWrite(ledBanheiro, LOW);
            }

          else if (readString.indexOf("?ledg1") > 0){
              digitalWrite(ledBanheiro, HIGH);
            }

          else if (readString.indexOf("?ledh0") > 0){//h
              digitalWrite(ledFrente, LOW);
            }

          else if (readString.indexOf("?ledh1") > 0){
              digitalWrite(ledFrente, HIGH);
            }

          else if (readString.indexOf("?alarmon") > 0){//alarme
              alarmeOnOff = true;
            }

          else if (readString.indexOf("?alarmoff") > 0){
              alarmeOnOff = false;
          }
          
          readString = "";
}


