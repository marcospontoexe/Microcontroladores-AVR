#include <Arduino.h>
#include <string.h>

void setup() {
  // DEFINES de UART
  #define UART_RX1 1
  #define UART_TX1 0
  #define UART_RX2 5
  #define UART_TX2 4
  #define BAUD_RATE 115200

  //Apenas para evitar queima das portas no momento da compilação, caso as portas TX e RX estejam curtocircuitadas
  pinMode(UART_RX1, INPUT);
  pinMode(UART_TX1, INPUT);
  pinMode(UART_RX2, INPUT);
  pinMode(UART_TX2, INPUT);

  
  Serial1.setRX(UART_RX1);
  Serial1.setTX(UART_TX1);
  Serial1.begin(BAUD_RATE);
  Serial2.setRX(UART_RX2);
  Serial2.setTX(UART_TX2);
  Serial2.begin(BAUD_RATE);
  
}


void loop() {
  uint8_t dados_ide[50] = {0}; //array inteiro sem sinal, de 8 bits.  
  uint8_t dados_uart1[50] = {0};
  uint8_t size_buff_ide = Serial.readBytes(dados_ide, sizeof(dados_ide));    //lê dados da porta serial da IDE para o array "dados_ide" e retorna o número de bytes lidos na variável "size_buff_ide"
  uint8_t size_buff_uart1 = Serial2.readBytes(dados_uart1, sizeof(dados_uart1));    //lê dados da porta serial da IDE para o array "dados" e retorna o número de bytes lidos na variável "tamanho_buff"

 
  // envia dados 
  if(size_buff_ide > 0)
  {            
    Serial.write(dados_ide, size_buff_ide);
    Serial2.write(dados_ide, size_buff_ide);   // envia dados pela UART1 
    
  }

  //recebe dados   
  if(size_buff_uart1 > 0) 
  {    
    Serial.write(dados_uart1, size_buff_uart1);    // envia os dados armazenados no array "dados" para a porta serial da IDE
    Serial2.write(dados_uart1, size_buff_uart1);   // envia um eco   
  } 

  delay(100); // Aguardar por um curto período  

}
