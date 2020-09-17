//Programa: Sensor de Chama com Arduino
//Modificado por último: 18/05
//Autor: Andreza Serra

int sensorChama = 7;

void setup() {
    Serial.begin(9600);
    pinMode(sensorChama, INPUT);
}


void loop() 
{
    Serial.println("Estado do Sensor de Chama: ");
    Serial.println(valor);

    if (valor != 1)
    {
      Serial.println("Fogo detectado!");
    }

    delay (1000);
}



