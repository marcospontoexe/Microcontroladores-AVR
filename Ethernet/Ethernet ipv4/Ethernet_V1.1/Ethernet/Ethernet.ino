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
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);


// telnet defaults to port 23
EthernetServer server(23);

//Chip Select pin
#define CS 17

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  Ethernet.init(CS);  // WIZnet W5100S-EVB-Pico W5500-EVB-Pico W6100-EVB-Pico

  // initialize the Ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);

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

  Serial.print("Server address:");
  Serial.println(Ethernet.localIP());
}

void loop() 
{
  EthernetClient client = server.available();   // retorna um objeto cliente que está conectado ao servidor e possui dados disponíveis para leitura.
    
  if (client) 
  {
    Serial.println("Cliente conectado");
    while(client.connected()) // retorna True ou False
    {          
      while(client.available()>0) // 'client.available()' retorna o número de bytes disponíveis para leitura
      {   
        char c = client.read();     //Lê o próximo byte recebido do servidor ao qual o cliente está conectado
        Serial.write(c); // Exibir o caractere recebido no monitor serial
        client.write(c); // Envia um eco para o próprio cliente 
      }
      /*
      String txt = Serial.readString(); //recebe a string digitada na serial do arduino
      int tamanho = txt.length();
      if(tamanho > 0)
      {
        server.print(txt);
        tamanho = 0;
      }
      */
      byte temp[100];      
      int len = Serial.readBytes(temp, 100);
      if(len > 0)
      {        
        server.write(temp, len);        
        len = 0;
      }
      
    }
    client.stop();
    Serial.println("Cliente desconectado");
  }
}
