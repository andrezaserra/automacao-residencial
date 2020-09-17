int sensorChama = 6;

void setup()
{
  pinMode(sensorChama, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.println();
}


char DetectarChama(int sensor)
{
  char chama = DetectarChama(sensorChama);
  if (digitalRead(sensor) =! 1)
  {
    return 'Fogo detectado!';
  }
  else 
  {
    return 'Nada de fogo, relaxa.';
  }
}
