

void setup() {
  Serial.begin(115200);
  Serial2.setTX(8);
  Serial2.setRX(9);
  Serial2.begin(115200);
}

void loop() {
  static String message = "";  // Variável para armazenar a mensagem acumulada
  uint16_t length = Serial2.available();  //retorna a quantidade de bytes disponíveis para leitura (o buffer de recebimento armazena até 64 bytes)


  if (length > 0) {
    for (uint8_t i = 0; i < length; i++) {
      char character = Serial2.read();
      if (character == '\n') {  // Se for um caractere de nova linha
        Serial.print("PDL recebendo: ");
        Serial.println(message);
        message = "";  // Limpa a mensagem acumulada
      } else {
        message += character;  // Adiciona o caractere à mensagem
      }
    }
  }
}
