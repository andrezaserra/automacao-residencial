//Programa : Webserver com aviso de acionamento de leds
//AUTOR: Arduino e Cia - MODIFICAÇÃO: Andreza Serra
// Baseado no programa exemplo Webserver, de David Mellis e Tom Igoe

#include <SPI.h> //inclusão da lib SPI
#include <Ethernet.h> //inclusão da lib Ethernet

// A linha abaixo define o MAC adress da Shield
byte mac[] = {  0x00, 0x00, 0x00, 0x00, 0x00, 0x01 };

// Os valores abaixo definem o endereço IP, gateway e máscara.
// Configure de acordo com a sua rede.
IPAddress ip(192, 168, 2, 150);      //Define o endereço IP
IPAddress gateway(192, 168, 2, 1); //Define o gateway
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede

// Inicializa um servidor com o nome de "server"
EthernetServer server(80); //o server será iniciado na porta 80

int pinoled = 8;  //Define o led1 na porta 8 analógica
int pinoled2 = 9; //Define o led2 na porta 9 analógica
char mensagem[20];   //Mensagem que será apresentada para o led1
char mensagem2[20];  //Mensagem que será apresentada para o led2

void setup() // código que é executado uma única vez (na inicialização)
{
  pinMode(pinoled, OUTPUT); //Define o led1 como entrada
  pinMode(pinoled2, OUTPUT); //Define o led2 como entrada
  digitalWrite(pinoled, LOW); // Define o status inicial do led como low (desligado, 0)
  digitalWrite(pinoled2, LOW); //Define o status inicial do led como low (desligado, 0)

  //Inicializa a conexao ethernet e o servidor web (na porta 80, definida anteriormente)
  Ethernet.begin(mac, ip, gateway, subnet); //Inicializa a lib Ethernet
  server.begin(); // Inicializa o EthernetServer (definido anteriormente como "server")
  
  Serial.print("server is at ");        //Imprime na tela a mensagem "server is at" (o server está em: )
  Serial.println(Ethernet.localIP());  // Imprime o Host onde o server está hospedado
}

void loop() //código que fica em loop
{
  //Verifica o status do led1 e imprime a mensagem no browser
  if (digitalRead(pinoled) == LOW)// se a leitura retornar que o led1 está desligado:
  {
    digitalWrite(pinoled, HIGH); // ligue-o

    char mensagem[20] = "Acionado !!!"; //"mensagem" assume o valor "Acionado !!!"
    char mensagem2[20] = "Aguardando..."; // "mensagem2" assume o valor "Aguardando..."

    apresentadados(mensagem, mensagem2); // Chama o método "apresentados" usando como
                                         //argumento as vars definidas acima

    delay(5000);   //Mantem o led aceso por 5 segundos

    apresentadados("Aguardando...", "Aguardando...");//Imprime mensagem padrao, aguardando novo acionamento
    digitalWrite(pinoled, LOW); // desliga o led
  }

  //Verifica o status do led2 e imprime a mensagem no browser
  if (digitalRead(pinoled2) == LOW)// se a leitura disser que o led2 está desligado:
  {
    digitalWrite(pinoled2, HIGH); // ligue-o

    char mensagem[20] = "Aguardando..."; //"mensagem" assume o valor "Aguardando..."
    char mensagem2[20] = "Acionado !!!"; // "mensagem2" assume o valor "Acionado !!!"

    apresentadados(mensagem, mensagem2); // Chama o método "apresentados" usando como
                                        //argumento as vars definidas acima

    delay(5000);  //Mantem o led aceso por 5 segundos

    apresentadados("Aguardando...", "Aguardando...");//Imprime mensagem padrao, aguardando novo acionamento
    
    digitalWrite(pinoled2, LOW); //desliga o led
  }
}

// CRIAÇÃO DO "MÉTODO" APRESENTADOS
// responsável pela impressão dos estados no browser (de maneira organizada)

void apresentadados(char msg[], char msg2[]) // Cria o método com nome "apresentados",
                                            //usando como argumentos duas strings
                                            // "msg[]" e "msg2[]" (ambas sem parâmetros)
{
  // OUVINDO AS ENTRADAS DO CLIENTE
  
  EthernetClient client = server.available(); //Cria um EthernetClient de nome "client" e atribui a ele a função available - 
                                             //(cliente que possui dados de leitura)

  //Executar para "client":
  if (client) {
    Serial.println("new client"); //Imprime a mensagem "new client" (novo cliente)
    
    
    //Requisição HTTP em branco:
    boolean currentLineIsBlank = true; //Cria a var "currentLineIsBlank" (a linha atual está em branco) como
                                      //tipo bool (v ou f) e a inicializa como TRUE (v)
    
    while (client.connected()) { //Enquanto "client" estiver conectado
      if (client.available()) { //Se "client" for do tipo available (possui dados de leitura)
        
        char c = client.read(); //Cria a var "c" do tipo char que recebe a leitura de "client"
        
        Serial.write(c); //Grava dados binários de "c" na porta serial (estes dados são enviados como um byte ou uma série de bytes)


        if (c == '\n') {        // se 'c' assumir o valor de uma nova linha ('\n')
          currentLineIsBlank = true;  //atribua valor VERDADEIRO à var "currentLineIsBlank"
        }

        if (c == '\n' && currentLineIsBlank) {      // se c assumir o valor de uma nova linha ('\n') e essa linha estiver em branco (currentLineIsBlank == TRUE)

          //o server deve enviar um cabeçalho padrão de resposta HTTP
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          
          //a conexão se encerra após a resposta
          client.println("Connection: close");

          // A página se atualiza a cada 5 segundos (como determinado no loop)
          client.println("Refresh: 0");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          
          // Mostrando o valor de saída de cada led
          client.print("Estado Led 1 : ");
          client.print(msg); // exibe o estado do led 1
          client.println("<br />");
          client.print("Estado Led 2 : ");
          client.print(msg2); // exibe o estado do led 2
          client.println("<br />");
          client.println("</html>");
          break;
        }

        else if (c != '\r') {          //Se a linha não for vazia
          currentLineIsBlank = false; //Atribua valor FALSO à currentLineIsBlank
        }
      }
    }

    
    // Dá um tempo ao navegador para o recebimento dos dados
    delay(1);
    
    // Para a conexão
    client.stop();
    Serial.println("client disconnected"); //Imprime que o cliente está desconectado
  }


  
}