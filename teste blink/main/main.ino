#include <avr/io.h>     // mapeamento dos registradores

void setup() {
  DDRB = 0b11011111;   // Botões PB1, PB2, PB3 e PB4 como pinos de entrada, PB5 é o Buzz, PB7 é o Led
  // put your setup code here, to run once:
  //pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(3, INPUT_PULLDOWN); 
    
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB = 0b10000000; // GPIO B5 e B4 Nível HIGH
  delay(1000);
  PORTB = 0b00000000; // GPIO B5 e B4 Nível LOW
  delay(1000);
   /* 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100); 
  */
}
