#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Largura do display em pixels
#define SCREEN_HEIGHT 32 // Altura do display em pixels
#define OLED_RESET    -1 // Define o pino de reset do display (opcional)
#define SSD1306_I2C_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);
  
  if(!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("Erro ao iniciar o display SSD1306"));
    while(true);
  }

  display.display(); // Limpa o buffer do display
  delay(2000);       // Pausa por 2 segundos
  display.clearDisplay(); // Limpa o display
}

void loop() {
  display.clearDisplay(); // Limpa o buffer do display

  // Escreve "Hello, World!" no display
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Hello, World!");

  display.display(); // Mostra o conteúdo do buffer no display
  delay(1000);       // Pausa por 1 segundo
}
