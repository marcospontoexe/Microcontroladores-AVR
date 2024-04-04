/*
 Advanced Chat Server

 A more advanced server that distributes any incoming messages
 to all connected clients but the client the message comes from.
 To use, telnet to your device's IP address and type.
 You can see the client's input in the serial monitor as well.
 Using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 redesigned to make use of operator== 25 Nov 2013
 by Norbert Truchsess

 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);


// telnet defaults to port 23
EthernetServer server(23);
EthernetClient clients[8];  //para gerenciar multiplos clientes

//Chip Select pin
#define CS 17

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(CS);  // WIZnet W5100S-EVB-Pico W5500-EVB-Pico W6100-EVB-Pico

  // initialize the Ethernet device
  Ethernet.begin(mac, ip, myDns, gateway, subnet);

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
     // wait for serial port to connect. Needed for native USB port only
  }

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start listening for clients
  server.begin();

  Serial.print("Chat server address:");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // check for any new client connecting, and say hello (before any incoming data)
  EthernetClient newClient = server.accept();
  if (newClient) {
    for (byte i=0; i < 8; i++) {
      if (!clients[i]) {
        Serial.print("We have a new client #");
        Serial.println(i);
        newClient.print("Hello, client number: ");
        newClient.println(i);
        // Once we "accept", the client is no longer tracked by EthernetServer
        // so we must store it into our list of clients
        clients[i] = newClient;
        break;
      }
    }
  }

  // check for incoming data from all clients
  for (byte i=0; i < 8; i++) {
    if (clients[i] && clients[i].available() > 0) {   // se 'clients[i]' não for NULL e se 'clients[i].available()' ter dados disponíveis para leitura no cliente do índice i. 
      // read bytes from a client
      byte buffer[80];    //criar um array de bytes, armazena até 80 elementos do tipo byte. (byte é um tipo de dado que pode armazenar valores inteiros de 0 a 255).
      
      // 'count' armazena o número real de bytes lidos a partir do buffer do cliente. 
      //O método 'read()' le os dados do buffer do cliente e armazena em 'buffer', 80 é o tamanho máximo de bytes a serem lidos do buffer do cliente.
      int count = clients[i].read(buffer, 80);    
      // os dados enviados por um cliente são retransmitidos para todos os outros clientes, exceto para o cliente de origem.
      for (byte j=0; j < 8; j++) {
        if (j != i && clients[j].connected()) {   // caso os índices 'i' e 'j' não seja os mesmos, e o método connected() garante que apenas os clientes ativos e conectados recebam os dados enviados pelo cliente de origem. 
          clients[j].write(buffer, count);    //envia dados para o cliente 'j'. O primeiro parâmetro é um ponteiro para os dados a serem enviados (no caso, o array buffer), e o segundo é o número de bytes a serem enviados (no caso, o valor de count).
        }
      }
    }
  }

  // stop any clients which disconnect
  for (byte i=0; i < 8; i++) {
    if (clients[i] && !clients[i].connected()) {  // se 'clients[i]' não for NULL e se 'clients[i]' estiver desconectado 
      Serial.print("disconnect client #");
      Serial.println(i);
      clients[i].stop();
    }
  }

  
}
