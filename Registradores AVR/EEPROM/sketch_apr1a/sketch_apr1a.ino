#include <avr/eeprom.h>   // para manipular a memória EEPROM
#include <EEPROM.h>
//#include <Arduino.h>

#define EEPROM_ADDR 0   // Endereço de memória na EEPROM onde os dados serão armazenados



void escreverNaEEPROM(uint8_t data) {   // Função para escrever um byte na EEPROM
    eeprom_write_byte((uint8_t*)EEPROM_ADDR, data);
    
}


uint8_t lerDaEEPROM() {   // Função para ler um byte da EEPROM
    return eeprom_read_byte((uint8_t*)EEPROM_ADDR);
    
}


void setup() {
  //uint8_t dadoParaGravar = 0xfe;
  //uint8_t dadoLido = 1;

  Serial.begin(9600);
  //delay(5000);
  //Serial.println(dadoLido);

  // Escrever um byte na EEPROM
  //escreverNaEEPROM(dadoParaGravar);

  // Ler o byte da EEPROM
  //dadoLido = lerDaEEPROM();

  // Imprimir o valor lido
  //Serial.println(dadoLido);
  
}

/*
void loop() {
  if (Serial.available() > 0) { // Verifica se há dados disponíveis na porta serial
    int valor = Serial.parseInt(); // Lê um valor inteiro da porta serial
    int teste = 0;
    // Verifica se o valor lido é válido (diferente de zero)
    if (valor != 0) {
      // Grava o valor na EEPROM na posição 0
      //escreverNaEEPROM(valor);
      EEPROM.put(EEPROM_ADDR, valor);
      Serial.print("Valor gravado na EEPROM: ");
      EEPROM.get(EEPROM_ADDR, teste);
      Serial.println(teste);
    } else {
      Serial.println("Valor inválido.");
    }
  }
}
*/

void loop() {
  if (Serial.available() > 0) { // Verifica se há dados disponíveis na porta serial
    int valor = Serial.read(); // Lê um valor inteiro da porta serial
    int teste = 0;
    // Verifica se o valor lido é válido (diferente de zero)
    if (valor != 0) {
      // Grava o valor na EEPROM na posição 0
      //escreverNaEEPROM(valor);
      eeprom_write_byte((uint8_t*)EEPROM_ADDR, valor);
      Serial.print("Valor gravado na EEPROM: ");
      teste = eeprom_read_byte((uint8_t*)EEPROM_ADDR);
      Serial.println(teste);
    } else {
      Serial.println("Valor inválido.");
    }
  }
}


