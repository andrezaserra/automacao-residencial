int led = 5;


void setup ()
{
  pinMode(led, INPUT);
  digitalWrite(led, HIGH);
  Serial.begin(9600);
}


void loop()
{
  Serial.print("O led está em: ");
  Serial.println(EstadoDoLed(led));
}

char EstadoDoLed (int led) // Função que retorna em string o estado de um led
{
  if (digitalRead(led) == HIGH){ // se o led estiger ligado
    return 'Ligado'; // retorne a palavra "Ligado"
  }
  else { //se não
    return 'Desligado'; // retorne a palavra "Desligado"
  } 
  
}
