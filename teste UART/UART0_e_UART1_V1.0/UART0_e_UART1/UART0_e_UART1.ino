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


void serial_communication()
{ 
  Serial1.printf("UART0 do micro...\n");
  Serial2.printf("UART1 do micro...\n");
  //delay(1000);
  // send data only when you receive data:
  if (Serial1.available() > 0) {
    // read the incoming byte:
    String incomingByte1 = Serial1.readString();
 

    // say what you got:
    Serial.print("IDE arduino recebendo: ");
    Serial.println(incomingByte1);
  } 
  if (Serial2.available() > 0) {
    // read the incoming byte:
    String incomingByte2 = Serial2.readString();
 

    // say what you got:
    Serial.print("IDE arduino recebendo: ");
    Serial.println(incomingByte2);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  serial_communication();
  
}
