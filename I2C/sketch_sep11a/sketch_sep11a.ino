#include <avr/io.h>             // mapeamento dos registradores
#include <avr/interrupt.h>     // rotinas de interrupção
#include <util/twi.h>          // códigos de status do TWI (TW_START, TW_MT_SLA_ACK...) e a macro TW_STATUS
#include "BIBLIOTECAS/UART.h"  // mesma caixa do nome do arquivo: "UART.H" só é encontrado em Windows

// Byte enviado logo depois do START: 7 bits de endereço + bit R/W no bit 0.
// 0x38 = 0b0011100_0 -> dispositivo de endereço 0x1C (7 bits) e operação de escrita (R/W = 0).
// Se o datasheet do seu dispositivo der o endereço 0x38 em 7 bits, o byte enviado deve ser 0x70 (0x38 << 1).
#define I2C_SLA_W  0b00111000
#define I2C_DADO   0x00        // byte enviado ao dispositivo: troque pelo registrador ou comando que ele espera

// mensagens enviadas pela UART (vetores de char porque UART_enviaString() recebe char*)
char msg_ok[]    = "I2C: dado enviado com ACK\r\n";
char msg_falha[] = "I2C: falhou, status 0x";
char msg_fim[]   = "\r\n";

// espera o TWI terminar a operação atual e devolve o código de status
unsigned char twi_aguarda(void) {
  while (!(TWCR & (1<<TWINT)));   // o hardware coloca o TWINT em 1 quando termina a operação
  return TW_STATUS;               // TWSR & 0xF8: descarta os 2 bits do prescaler
}

// faz uma escrita completa: START, endereço + W, um byte de dado e STOP
// devolve o status da última etapa executada; TW_MT_DATA_ACK (0x28) indica sucesso
unsigned char i2c_envia(unsigned char sla_w, unsigned char dado) {
  unsigned char status;

  // envia a condição de start
  TWCR = ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN)); // zera o TWINT (escrevendo 1), mantém o periférico habilitado e manda o START
  status = twi_aguarda();
  if (status != TW_START) {       // barramento ocupado ou arbitragem perdida: o START não saiu, então não há STOP a mandar
    return status;
  }

  // envia o endereço do dispositivo e o bit de R/W
  TWDR = sla_w;
  TWCR = ((1<< TWINT) | (1<<TWEN));   // zera o bit de interrupção novamente e habilita a comunicação
  status = twi_aguarda();             // TW_MT_SLA_ACK (0x18) se o dispositivo respondeu ao endereço

  if (status == TW_MT_SLA_ACK) {
    // envia o dado ao periférico
    TWDR = dado;
    TWCR = ((1<< TWINT) | (1<<TWEN));
    status = twi_aguarda();           // TW_MT_DATA_ACK (0x28) se o dispositivo aceitou o dado
  }

  // stop bit: libera o barramento mesmo quando o endereço ou o dado não receberam ACK
  TWCR = ((1<< TWINT) | (1<<TWEN) | (1<<TWSTO));
  while (TWCR & (1<<TWSTO));          // o hardware zera o TWSTO quando o STOP termina; só então pode haver outro START

  return status;
}

void setup() {
  // configuração do módulo I2C
  /* calculando a frequência do SCL
  SCL = (Fosc) / (16 + (2 * TWBR * prescaler))
  SCL = 16000000 / (16 + (2 * 18 * 4)) = 100 kHz
  */
  DDRC = 0b00110000;  // SDA (PC4) e SCL (PC5). Com TWEN = 1 o TWI assume o controle desses pinos, então esta linha não é obrigatória
  TWSR |= 0b00000001;   // prescaler = 4
  TWBR = 18;    //fator de divisão para geração de 100Khz
  TWCR = 0b00000100;    // habilita o módulo TWI(i2c) -> TWEN =1

  //configuração da comunicação uart
  UART_config();    // define um baudrate de 9600
  UCSR0B &= ~(1<<RXCIE0);   // o UART.h liga a interrupção de recepção, mas este sketch não tem ISR(USART_RX_vect): um byte recebido poderia reiniciar o programa
}

void loop() {
  unsigned char status = i2c_envia(I2C_SLA_W, I2C_DADO);   // START, endereço, dado e STOP

  if (status == TW_MT_DATA_ACK) {
    UART_enviaString(msg_ok);
  } else {
    UART_enviaString(msg_falha);
    UART_enviaHex(status);      // compare com a tabela de status do datasheet (ex.: 0x20 = ninguém respondeu ao endereço)
    UART_enviaString(msg_fim);
  }

  delay(1000);   // repete a escrita a cada 1 s
}
