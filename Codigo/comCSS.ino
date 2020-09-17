//INSERÇÃO DO CSS NO ESCOPO DO PROJETO DE AUTOMAÇÃO RESIDENCIAL

#include <SPI.h> //inclusão da lib SPI
#include <Ethernet.h> //inclusão da lib Ethernet
#include <DHT.h> //inclusão da lib do sensor DHT de umidade e temperatura

//Definiçôes DHT (serão usadas para setar o sensor DHT mais abaixo)
#define DHTPin A8 // pino em que o sensor será conectado (analógico 8)
#define DHType DHT11 // tipo do sensor DHT (DHT11)


// A linha abaixo define o MAC adress do Shield Ehternet
byte mac[] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };


// Os valores abaixo definem o endereço IP e máscara de sub-rede.
// Configurada de acordo com a rede local onde o sistema será implantado.
IPAddress ip(192, 168, 1, 235);      //Define o endereço IP
IPAddress subnet(255, 255, 255, 0); //Define a máscara


// Inicializa um servidor com o nome de "server"
EthernetServer server(80); // será iniciado na porta 80

// DECLARAÇÃO DE VARIÁVEIS DO PROJETO E MAPEAMENTO DE PORTAS:
const int ledSalaEstar = 30;
const int ledCozinha = 32;
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
const int buzzer = 3;


String readString; // Variável que lê as requisições do index da interface web de automação

//*********************************
/**/boolean alarmeOnOff = false;//*  //Variável que define o estado do alarme (ligado == true ou desligado == false)
//*********************************

//-------------------------------------- Sensor de Umidade e Temperatura   ------------------------------------
DHT sensorDHT(DHTPin, DHType); // inicia um DHT com nome  de variavel sensorDHT (sensor dht11, na porta analógica 8. Como definido anteriormente)
//-------------------------------------------------------------------------------------------------------------


void setup()
{
  // **********************************CONFIGURAÇÕES DE PINAGEM DE CADA VARIÁVEL*******************************************

  // todos os leds iniciam como saída de dados e estado inativo
  pinMode(ledSalaEstar, OUTPUT);
  digitalWrite(ledSalaEstar, LOW);

  pinMode(ledCozinha, OUTPUT);
  digitalWrite(ledCozinha, LOW);
  
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

  //A linha abaixo inicializa a conexao ethernet e o servidor
  Ethernet.begin(mac, ip, subnet); //Inicializa a lib Ethernet com os valores de mac, ip e subnet definidos anteriormente
  server.begin(); // Inicia o EthernetServer (definido anteriormente como "server")

  sensorDHT.begin(); //Inicia o sensor dht

}

void loop()
{
  Alarme(); // Chama a função Alarme (Definida logo abaixo do loop)
  Jardim(); // Chama a função Jardim (Definida logo abaixo do loop)

  //Depois da qustão do alarme ser estabelecida...
  EthernetClient client = server.available(); // Um EthernetClient de nome client é criado, com o valor de disponível
  if (client) {
    while (client.connected()) { // as linhas abaixo só serão executadas ENQUANTO client estiver conectado
      if (client.available()) { // as linhas abaixo só serão executados SE client estiver disponível
        char c = client.read(); 

        if (readString.length() < 100) {
          readString += c;
        }

        if (c == '\n') {
          //Início da página (interface web de automação)
          client.println("<!DOCTYPE html>"); 
          client.println("<html>"); 
          client.println("<meta charset = 'utf-8' />");
          client.println("<meta http-equiv=\"refresh\" content=\"10\">");

          client.println("<head>");
          client.println("<title>Automação Residencial</title>"); 
          client.println("</head>"); 

          client.println("<font color=#00ff00><strong> xxumidadexx </strong></font>>");
          client.println("<h1> Leitura dos Sensores </h1>"); 
          client.println("<p>");
          client.print("Sensor de Chama: ");
          client.print(EstadoChama()); 
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
          client.println("<a href=\"/ ?leda1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a>"); 
          client.println("<a href=\"/ ?leda0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>");

          
          client.println("<br>"); 
          client.print("Cozinha: "); 
          client.print(EstadoDoLed(ledCozinha)); 
          client.println("<a href=\"/ ?ledb1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>"); 
          client.println("<a href=\"/ ?ledb0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>"); 
          
          
          
          client.println("<br>"); 
          client.print("Garagem: "); 
          client.print(EstadoDoLed(ledGaragem)); 
          client.println("<a href=\"/ ?ledc1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>"); 
          client.println("<a href=\"/ ?ledc0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>"); 
          client.println("<br>"); 
          client.println("</p>"); 

          client.println("<h3>Primeiro Andar</h3>"); 
          client.println("<p>"); 
          client.print("Sala de TV: "); 
          client.print(EstadoDoLed(ledSalaTV)); 
          client.println("<a href=\"/ ?ledd1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>"); 
          client.println("<a href=\"/ ?ledd0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>"); 


          
          client.println("<br>"); 
          client.print("Quarto 1: "); 
          client.print(EstadoDoLed(ledQuarto1)); 
          client.println("<a href=\"/ ?lede1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>"); 
          client.println("<a href=\"/ ?lede0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>"); 

          
          client.println("<br>"); 
          client.print("Quarto 2: "); 
          client.print(EstadoDoLed(ledQuarto2)); 
          client.println("<a href=\"/ ?ledf1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>"); 
          client.println("<a href=\"/ ?ledf0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>"); 

          
          client.println("<br>"); 
          client.print("Banheiro: "); 
          client.print(EstadoDoLed(ledBanheiro)); 
          client.println("<a href=\"/ ?ledg1 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> LIGAR </b></button> </a><br/>");  
          client.println("<a href=\"/ ?ledg0 \"/> <button style='border: 2px solid #00CD00;' type='button'><b> DESLIGAR </b></button> </a><br/>"); 

          
          client.println("<br>");
          client.println("</p>"); 
          client.println("<h3>Jardim</h3>"); 
          client.print(EstadoDoLed(ledFrente)); 
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

} // fim do loop



//*************************************DEFINIÇÃO DAS FUNÇÕES DO PROJETO*******************************************************

///////////////////////////////ESTADO DO LED//////////////////////////////////
String EstadoDoLed (int inled) // Função que retorna em string o estado de um led e usa como um argumento uma var int correspondende a um led
{
  String resposta;
  if (digitalRead(inled) == HIGH) { // se o led estiver ligado
    resposta = "<font color=#00ff00><strong> LIGADO </strong></font> "; 
    return resposta; // a função vai retornar o texto "Ligado"
  } else { //se não
    resposta = "<font color=#ff0000><strong> DESLIGADO </strong></font> ";
    return resposta; // a função vai retornar o texto "Ligado"
  }

}// fim da função


///////////////////////////////ESTADO ALARME////////////////////////////////////////////

String EstadoDoAlarme (bool estado) // Função que retorna em string o estado do alarme e usa com um argumento uma var bool correspondente ao estado do alarme
{
  String resposta;
  if (estado == true) { //se essa var estiver em TRUE
    resposta = "<font color=#00ff00><strong> LIGADO </strong></font> ";
    return resposta; // a função vai retornar o texto "Ligado"
  } else { //se não
    resposta = "<font color=#ff0000><strong> DESLIGADO </strong></font> ";
    return resposta; // a função vai retornar o texto "Ligado"
  }

} //fim da função

//////////////////////////////////////////////////  ALARME //////////////////////////////////////////////////////////////////////////////
void Alarme() // Essa função tem como argumentos o buzzer e o sensor de presença (responsáveis pelo alarme da casa)
{
  if (alarmeOnOff == true) { // Se o estado do alarme for ativo:
    if  (digitalRead(sensorPresenca) == 1) // e se alguma presença for detectada pelo PIR
    {
      digitalWrite(buzzer, HIGH); // o buzzer deverá soar
    }
    else if (digitalRead(sensorPresenca) == 1) // e se nenhuma presença for detectada pelo PIR
    {
      digitalWrite(buzzer, LOW); // o buzzer não deverá soar
    }
  }else { }
}  //fim da função


///////////////////////////////////////ESTADO CHAMA////////////////////////////////////////////////////

String EstadoChama() // Função que retorna em string o estado do sensor de chama
{
  int estado = digitalRead(sensorChama);
  String resposta;
  if (estado == 1) // se a leitura do pino do sensor for 1
  {
    resposta = "<font color=#3366cc><strong> SEM PERIGO </strong></font> ";
    return resposta;// A função retorna que o fogo foi detectado
  }
  else //se não
  {
    resposta = "<font color=#ff0000><strong>  CALL 911 - EMERGÊNCIA - OH GOD </strong></font> ";
    return resposta; // A função retorna que o fogo não foi detectado
  }
  return resposta = "Não detectado, favor verificar sensor."; //default
} //fim da função



///////////////////////////////////////JARDIM/////////////////////////////////////////////////////
void Jardim() // Função que determina o comportamento dos leds do jardim
{
  int estado = analogRead(sensorLuminosidade);  //Lê o valor fornecido pelo LDR   
  if (estado > 800) // Caso o valor lido na porta analógica seja maior do que 800, os leds do jardim são acesos    
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

///////////////////////////////////IFS/////////////////////////////////////////////////////////
void IfsButtons() // Função determinada apenas para separar esse setor de verificações do loop
{
          if(readString.indexOf("?leda1") > 0) //se a requisição do index for ?leda1
          {
            digitalWrite(ledSalaEstar, HIGH); //ledSalaEstar é ligado
          }

          else if (readString.indexOf("?leda0") > 0){ //se a requisição do index for ?leda0
              digitalWrite(ledSalaEstar, LOW); //ledSalaEstar é desligado
            }
            
          else if (readString.indexOf("?ledb1") > 0){ //se a requisição do index for ?ledb1
              digitalWrite(ledCozinha, HIGH); //ledCozinha é ligado
            }

          else if (readString.indexOf("?ledb0") > 0){ //se a requisição do index for ?ledb0
              digitalWrite(ledCozinha, LOW); //ledCozinha é desligado
            }
         
          else if (readString.indexOf("?ledc0") > 0){ //se a requisição do index for ?ledb0
              digitalWrite(ledGaragem, LOW); //ledGaragem é desligado
            }

          else if (readString.indexOf("?ledc1") > 0){ //se a requisição do index for ?ledc1
              digitalWrite(ledGaragem, HIGH); //ledGaragem é ligado
            }

          else if (readString.indexOf("?ledd0") > 0){ //se a requisição do index for ?ledd0
              digitalWrite(ledSalaTV, LOW); //ledSalaTV é desligado
            }

          else if (readString.indexOf("?ledd1") > 0){ //se a requisição do index for ?ledd1
              digitalWrite(ledSalaTV, HIGH); //ledSalaTV é ligado
            }

          else if (readString.indexOf("?lede0") > 0){ //se a requisição do index for ?lede0
              digitalWrite(ledQuarto1, LOW); //ledQuarto1 é desligado
            }

          else if (readString.indexOf("?lede1") > 0){ //se a requisição do index for ?lede1
              digitalWrite(ledQuarto1, HIGH); //ledQuarto1 é ligado
            }

          else if (readString.indexOf("?ledf0") > 0){ //se a requisição do index for ?ledf0
              digitalWrite(ledQuarto2, LOW); //ledQuarto2 é desligado
            }

          else if (readString.indexOf("?ledf1") > 0){ //se a requisição do index for ?ledf1
              digitalWrite(ledQuarto2, HIGH); //ledQuarto2 é ligado
            }          

          else if (readString.indexOf("?ledg0") > 0){ //se a requisição do index for ?ledg0
              digitalWrite(ledBanheiro, LOW); //ledBanheiro é desligado
            }

          else if (readString.indexOf("?ledg1") > 0){ //se a requisição do index for ?ledg1
              digitalWrite(ledBanheiro, HIGH); //ledBanheiro é ligado
            }

          else if (readString.indexOf("?ledh0") > 0){ //se a requisição do index for ?ledh0
              digitalWrite(ledFrente, LOW); //ledFrente é desligado
            }

          else if (readString.indexOf("?ledh1") > 0){ //se a requisição do index for ?ledh1
              digitalWrite(ledFrente, HIGH); //ledFrente é ligado
            }

          else if (readString.indexOf("?alarmon") > 0){ //se a requisição do index for ?alarmon
              alarmeOnOff = true; //a variável de estado do alarme assume valor TRUE
            }

          else if (readString.indexOf("?alarmoff") > 0){ //se a requisição do index for ?alarmoff
              alarmeOnOff = false; //a variável de estado do alarme assume valor FALSE
          }
          
          readString = ""; //Zera a variável de leitura do index
}


