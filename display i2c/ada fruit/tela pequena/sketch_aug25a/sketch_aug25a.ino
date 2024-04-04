#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Largura do display em pixels
#define SCREEN_HEIGHT 32 // Altura do display em pixels
#define OLED_RESET    -1 // Pino de reset do display (opcional)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Inicializa o display com endereço 0x3C (Padrão para o SSD1306)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Erro ao iniciar o display SSD1306"));
    while(true);
  }
  else{Serial.println("OK");}
  
  display.clearDisplay(); // Limpa o buffer do display
  display.setTextSize(1); // Tamanho do texto
  display.setTextColor(SSD1306_WHITE); // Cor do texto
  display.setCursor(0, 0); // Posição do cursor
}

void loop() {
  display.clearDisplay(); // Limpa o buffer do display
  
  // Imprime a mensagem no display
  display.print("Olá, Mundo!");
  
  display.display(); // Mostra o conteúdo do buffer no display
  
  delay(1000); // Pausa de 1 segundo
}
