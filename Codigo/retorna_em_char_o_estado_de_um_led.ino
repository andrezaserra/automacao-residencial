int led_1 = 3;
int led_2 = 4;

void setup()
{
  pinMode(led_1, INPUT);
  digitalWrite(led_1, HIGH);

  pinMode(led_2, INPUT);
  digitalWrite(led_2, HIGH);

  Serial.begin(9600);
}

void loop()
{
  Serial.print("Led 1: ");
  Serial.println(EstadoDoLed(led_1));
  Serial.print("Led 2: ");
  Serial.println(EstadoDoLed(led_2));
}

char EstadoDoLed (int led) // Função que retorna em string o estado de um led
{
  if (digitalRead(led) == HIGH){ // se o led estiger ligado
    return 'Ligado'; // retorne a palavra "Ligado"
  }
  else if (digitalRead(led) == LOW) { //se não
    return 'Desligado'; // retorne a palavra "Desligado"
  } 
}
