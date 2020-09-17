void MostrarNaSerial()
{
   Serial.begin(9600);
 Serial.println("************************************* TESTE *****************************************");
 Serial.println(""); 
 Serial.println("SENSORES:");
 Serial.print("Umidade: ");
 Serial.println(Umidade());
 Serial.print("Temperatura: ");
 Serial.println(Temperatura());
 Serial.print("Chama: ");
 Serial.println(EstadoChama());
 Serial.println("");
 Serial.println("ESTADO DOS LEDS:");
 Serial.print("Led 1: ");
 Serial.println(EstadoDoLed(led_1));
 Serial.print("Led 2: ");
 Serial.println(EstadoDoLed(led_2));
}


