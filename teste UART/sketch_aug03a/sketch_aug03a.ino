#include <Arduino.h>
#include <string.h>

void setup() {
  // put your setup code here, to run once:
  #define UART_RX 1
  #define UART_TX 0
  #define BAUD_RATE 115200

  pinMode(UART_RX, INPUT);
  pinMode(UART_TX, INPUT);

  Serial.begin(BAUD_RATE);
  delay(1000);
  Serial1.setRX(UART_RX);
  Serial1.setTX(UART_TX);
  Serial1.begin(BAUD_RATE);
  delay(1000);
  
}
/*
void serial_configure()
{
    Serial.begin(BAUD_RATE);
    delay(1000);
    Serial2.setRX(UART_RX);
    Serial2.setTX(UART_TX);
    Serial2.begin(BAUD_RATE);
    delay(1000);
}
*/

void serial_communication()
{
  Serial1.printf("UART do micro...\n");
  // send data only when you receive data:
  if (Serial1.available() > 0) {
    // read the incoming byte:
    String incomingByte = Serial1.readString();
 

    // say what you got:
    Serial.print("IDE arduino recebendo: ");
    Serial.println(incomingByte);
  } 
}

void loop() {
  // put your main code here, to run repeatedly:
  serial_communication();
  
}
