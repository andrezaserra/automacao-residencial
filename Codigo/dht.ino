#include <DHT.h> 
#define DHTPin A1 // pino que estamos conectado
#define DHType DHT11 // DHT 11

 
void setup()
{
  DHT sensorDHT(DHTPin, DHType); // cria uma instância da lib DHT com nome sensorDHT
  sensorDHT.begin(); // incia essa instância
}

void loop ()
{
  DHT sensorDHT(DHTPin, DHType);
  sensorDHT.begin();
}


char Umidade(DHT sensor)
{
  float UmidadeFloat = sensor.readHumidity();
  char UmidadeChar = UmidadeFloat;
  return UmidadeChar;
}

char Temperatura(DHT sensor)
{
  float TemperaturaFloat = sensor.readTemperature();
  char TemperaturaChar = TemperaturaFloat;
  return TemperaturaChar;
}
