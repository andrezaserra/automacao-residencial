
#include <SPI.h>
#include <Ethernet.h>
// Objetivo: transformar Arduino Uno em um webserver capaz de ficar escutando a porta 80
// para receber pedido de um browser cliente e ligar ou desligar um led
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 1, 250 };
int ledPin = 9; // Define o pino digital 9 do led a ser ligado/desligado
char buffer[128]; // Armazena caracteres que o webserver lÃª do browser
int i = 0; // EndereÃ§o posiÃ§Ã£o array buffer
EthernetServer server(80); // Inicia servidor na porta 80
void setup() {
Ethernet.begin(mac, ip);
server.begin();
pinMode(ledPin, OUTPUT);
}


void loop() {
EthernetClient cliente = server.available();
if (cliente) {
boolean linhaVazia = true;
while (cliente.available()) {
char c = cliente.read();
if (c == '\n' && linhaVazia) { // Se o fim da linha for '\n' e a linha estiver em branco significa fim da solicitaÃ§Ã£o HTTP
cliente.println("HTTP/1.1 200 OK");
cliente.println("Content-Type: text/html\n");
cliente.println("<html><body><h3>Resposta do Arduino</h3><br />");
if (strstr(buffer, "?statusled=on")) {
cliente.println("LED ligado");
digitalWrite(ledPin, HIGH);
}
else
if (strstr(buffer, "?statusled=off")) {
cliente.println("LED desligado");
digitalWrite(ledPin, LOW);
}
else
cliente.println("NÃ£o foi possÃ­vel ligar ou desligar o LED");
cliente.println("</body></html>");
break;
}
if (c == '\n')
linhaVazia = true;
else
if (c != '\r') { // Ainda existem caracteres a serem lidos
linhaVazia = false;
buffer[i++] = c;
}
}
delay(10); // Permite ao browser receber a resposta
cliente.stop(); // Desconecta cliente do servidor
}
}
