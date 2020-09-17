int led = 9;

void setup(){}

void loop()
{
  FuncaoAlteraEstado(led);
}

void FuncaoAlteraEstado (int led)
{
  if (digitalRead(led) == HIGH)
  {
    return digitalWrite(led, LOW);
  }
  else if (digitalRead(led) == LOW)
  {
    return digitalWrite(led, HIGH);
  }
}

