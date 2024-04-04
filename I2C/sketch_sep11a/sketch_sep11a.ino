#include <avr/io.h>             // mapeamento dos registradores
#include <avr/interrupt.h>     // rotinas de interrupção
#include "BIBLIOTECAS/UART.H"    

void setup() {
  // configuração do módulo I2C
  /* calculando a frequência do SCL
  SCL = (Fosc) / (16 + (2 * TWBR * prescaler))  
  */
  DDRC = 0b00110000;  //os pinos de SDA(PC4) e SCL(PC5) precisão ser definidos como saida
  TWSR |= 0b00000001;   // prescaler = 4
  TWBR = 18;    //fator de divisão para geração de 100Khz
  TWCR = 0b00000100;    // habilita o módulo TWI(i2c) -> TWEN =1

  //configuração da comunicação uart
  UART_config();    // define um baudrate de 9600


}

void loop() {
  // variáveis para armazenar a leitura do I2C
  unsigned char i2cReg1 = 0;
  unsigned char i2cReg2 = 0;

  
  // envia a condicção de start
  TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN)); // desabilita interrução, habilita o periférico, manda bit de start
  while (!(TWCR & (1<<TWINT)));   // aguarda o TWINT virar HIGH, indicando que o START foi enviado
      
  // envia o endereço do dispositivo e o bit de R/W
  TWDR = 0b00111000;  //0x38. O bit 0 é responsável pela escrita ou leitura, quando for 0 o mestre está escrevendo, quando 1 o mestre esta lendo

  TWCR = ((1<< TWINT) | (1<<TWEN));   // zera o bit de interrupção novamente e habilita a comunicação
  while (!(TWCR & (1 <<TWINT)));      // aguarda a comunicação ser completada

  // envia  dado ao periférico
  TWDR = dado;
  TWCR = ((1<< TWINT) | (1<<TWEN));
  while (!(TWCR & (1 <<TWINT)));

  // stop bit
  TWCR = ((1<< TWINT) | (1<<TWEN) | (1<<TWSTO));

}
