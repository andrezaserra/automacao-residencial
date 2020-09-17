//modificado pela última vez: 18/05

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
int sensorLDR = 4;
int buzzer = 3;

int sensorDHT = A8;

void setup(){
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
  
  pinMode(sensorChama, INPUT);
  
  pinMode(sensorPresenca, INPUT);
  
  pinMode(sensorLDR, INPUT);
  
  pinMode(buzzer, OUTPUT);
  
  pinMode(sensorDHT, INPUT);
}

void loop(){}
