// modificado pela última vez em: 18/05

int sensorPresenca = 8;
int buzzer = 10;
boolean alarme;

void setup()
{
  pinMode(sensorPresenca, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  alarme = true;
  FuncaoAlarme(sensorPresenca, buzzer, alarme);
}



void FuncaoAlarme(int sensorPresenca, int buzzer, boolean alarme)
{
  if (alarme == true){
    Serial.println("Alarme ligado");
    while (digitalRead(sensorPresenca) == HIGH)
      {
        digitalWrite(buzzer, HIGH);
        Serial.println("Presença detectada!!");
      }
     
  }
  
  else if(alarme == false)
  {
    Serial.println("Alarme desligado");
  }
 
}
