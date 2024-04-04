#include <avr/io.h>     // mapeamento dos registradores
#include <avr/interrupt.h>     // rotinas de interrupção

#define CLOCK 20000000

volatile unsigned short int cont_inicial = (256) - ((0.01*CLOCK)/1024);    // para um tempo de estouro de 10 ms
volatile int i = 0;

//------------------interrupções-------------------------
// PCINT0_vect monitora as interrupções ocorridas pelos pinos PCINT0 até PCINT7
// PCINT1_vect monitora as interrupções ocorridas pelos pinos PCINT8 até PCINT15
ISR(PCINT0_vect){  // a interrupção é gerada tanto para borda de subida quando para borda de descida
  delay(100);   //tratamento de debounce
  Serial.println((PINB & 0b00000010) == 0b00000010);
  if(!((PINB & 0b00000010) == 0b00000010)) // quando o B1 for para HIGH (apenas na borda de subida )
  {
    Serial.println("botão apertado");
  }
}

//-------------interrupção por timer--------------------------
ISR(TIMER2_OVF_vect){   //a cada 287 ms
  i++;
  if(i == 37){     // a cada 1 s    
    Serial.println("estouro");
    i =0;
  }  
  
  TCNT2 = cont_inicial;      // Configura o valor inicial do contador do timer1
}

void setup() {

  Serial.begin(9600);
  // configurando a direção dos GPIOs
  //DDRB = DDRB | 0b00110000;   //configura o GPIO B5 e B4 como saida e o restante como entrada
  DDRB = 0b00110000;   //configura o GPIO B5 e B4 como saida e o restante como entrada
  PORTB = 0b00000001; // GPIO B0 como pull up, o restando como pull down
  //PORTB = PORTB &~ 0b00001000; // GPIO B3 como pull down

  // configura pinos de interrupção
  PCICR = 0b00000001;     // habilita a o registrador PCIE0 (responsável pelos pinos PCINT0 até PCINT7)
  // PCMSK0 é responsável pelos registradores PCINT0 até PCINT7
  // PCMSK1 é responsável pelos registradores PCINT8 até PCINT15
  PCMSK0 = 0b00000010;      // Interrupção no PCINT1 (pino B1) habilitada

  // Configurando o TIMER2
  /*-----------CONTAGEM DE TEMPO--------------------------
  valor inicial da contagem = (256) - ((tempo desejado*Fosc)/prescaler)
  estoura a cada 1s para Fosc de 16Mhz -> valor inicial = (256) - ((1*16000000)/1024) = 49911
  ------------------------------------------------------*/
  /*-----------CONTAGEM DE ESTOURO--------------------------
   * para um contador de 16 bits
  tempo = (256 * prescaler) / (Fosc)  
  ------------------------------------------------------*/
  // TCCR1A é usado para comparadores (output compare)
  TCCR2B = 0b00000111; //Controla o prescaler (Prescaling de 1024)do timer2
  TCNT2 = cont_inicial;      // Configura o valor inicial do contador do timer2
  TIMSK2 = 0b00000001;  // habilita interrupção por estouro de tempo no timer2  
  

  /*
  Serial.print("cont_inicial: ");
  Serial.println(cont_inicial);
  for(unsigned short int i=0; i<=65536; i++){
    Serial.println(TCNT2);
  }
  */
  
  sei();      // set Global Interrupt Enable (habilita a chavel geral das interrupções)
}

void loop() {
  
  int valor = PINB & 0b00001000; // lê o estado do pino B3

  if(!(valor == 0b00001000)){      // quando B3 esta em nível low
    delay(50);
    while(!( (PINB & 0b00001000) == 0b00001000) ){
      
      
      
      } //tratamento de debounce
    
    PORTB = PORTB | 0b00100000; // GPIO B5 e B4 Nível HIGH
    delay(1000);
    PORTB = PORTB &~ 0b00100000; // GPIO B5 e B4 Nível LOW
    delay(1000);
    PORTB = PORTB | 0b00100000; // GPIO B5 e B4 Nível HIGH
    delay(1000);
    PORTB = PORTB &~ 0b00100000; // GPIO B5 e B4 Nível LOW
    delay(1000);
  }
  
  PORTB = PORTB ^ 0b00100000;  //inverte o estado lógico do pino B5
  delay(100);
    
}
