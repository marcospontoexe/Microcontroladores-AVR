#include <avr/interrupt.h>     // rotinas de interrupção
#include <avr/io.h>     // mapeamento dos registradores
#include <Arduino.h>


#define FOSC 16000000

volatile unsigned int cont_inicial = (65536) - ((0.001*FOSC)/64);    // para um tempo de estouro de 1 ms -> 65286
volatile unsigned int cont = 0;

//-------------interrupção por timer1--------------------------
ISR(TIMER1_OVF_vect){   //a cada 1 ms
  TCNT1 = cont_inicial;      // Configura o valor inicial do contador do timer1
  //Serial.println("Estouro");
  
  cont++;
  if(cont == 1000){
    Serial.println("Estouro");
    cont = 0;
  }  
  
}

void setup(){
  Serial.begin(9600);
  /*-----------CONTAGEM DE TEMPO--------------------------
  valor inicial da contagem = (65536) - ((tempo desejado*Fosc)/prescaler)
  estoura a cada 1 ms para Fosc de 16Mhz -> valor inicial = (65536) - ((1*16000000)/64) = 65286
  ------------------------------------------------------*/
  /*-----------CONTAGEM DE ESTOURO--------------------------
   * para um contador de 16 bits
  tempo = (65536 * prescaler) / (Fosc)  
  tempo = (65536 * 64) / (16000000) = 512 us
  ------------------------------------------------------*/
  //*********Configurando o TIMER1**************
  TCCR1A = 0;                        //configura timer1 para operação normal pinos OC1A e OC1B desconectados
  TCCR1B = 0b00000011; //Controla o prescaler (Prescaling de 1024)do timer1
  TCNT1 = cont_inicial;      // Configura o valor inicial do contador do timer1
  TIMSK1 = 0b00000001;  // habilita interrupção por estouro de tempo no timer1 

}

void loop() {  
 
    
}
