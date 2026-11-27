// Envia pela UART1 (Serial2: GPIO 8 = TX, GPIO 9 = RX) o que for digitado no monitor serial da IDE
// e mostra no monitor, linha por linha, o que chegar pela UART1.
// Para testar com uma placa só, ligue o GPIO 8 ao GPIO 9 (loopback).
// No monitor serial, escolha um final de linha que inclua "Nova linha" (NL), porque a mensagem só é mostrada ao chegar o '\n'.

void setup() {
  Serial.begin(115200);
  Serial2.setTX(8);
  Serial2.setRX(9);
  Serial2.begin(115200);
}

void loop() {
  static String message = "";  // Variável para armazenar a mensagem acumulada

  // envia: repassa para a UART1, byte a byte, o que foi digitado no monitor serial
  while (Serial.available() > 0) {          // só lê o que já chegou; o readString() usado antes travava o loop por 1 s a cada volta
    Serial2.write((uint8_t)Serial.read());  // write(uint8_t) envia o byte sem conversão para texto
  }

  // recebe: monta a mensagem com os caracteres que chegam pela UART1 até encontrar o '\n'
  while (Serial2.available() > 0) {
    char character = Serial2.read();  // read() devolve um caractere por vez; readString() devolvia tudo numa String, que não pode ser comparada com '\n'
    if (character == '\n') {  // Se for um caractere de nova linha
      Serial.print("PDL recebendo: ");
      Serial.println(message);
      message = "";  // Limpa a mensagem acumulada
    } else if (character != '\r') {  // ignora o '\r' do final de linha "NL e CR"
      message += character;  // Adiciona o caractere à mensagem
    }
  }
}
