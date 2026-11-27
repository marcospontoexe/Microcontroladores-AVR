/*
     CÓDIGO:  Q0624
     AUTOR:   BrincandoComIdeias
     LINK:    https://www.youtube.com/brincandocomideias ; https://cursodearduino.net/ ; https://cursoderobotica.net
     COMPRE:  https://www.arducore.com.br/
     SKETCH:  Exemplo LiquidCrystal_I2C
     DATA:    11/02/2020
*/

// INCLUSÃO DE BIBLIOTECAS
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// DEFINIÇÕES
#define endereco  0x27 // PCF8574 com os jumpers A0-A2 abertos. Outro comum: 0x3F (PCF8574A). Confirme com o I2C_scanner (o 0x7C usado antes fica na faixa reservada do I2C, 0x78-0x7F)
#define colunas   16
#define linhas    2

// INSTANCIANDO OBJETOS
LiquidCrystal_I2C lcd(endereco, colunas, linhas);

void setup() {
  lcd.init(); // INICIA A COMUNICAÇÃO COM O DISPLAY
  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY
  lcd.clear(); // LIMPA O DISPLAY

  lcd.print("- Ola, Mundo! -");
  delay(5000); // DELAY DE 5 SEGUNDOS
  lcd.setCursor(0, 1); // POSICIONA O CURSOR NA PRIMEIRA COLUNA DA LINHA 2
  lcd.print("Fim do Setup ()");
  delay(5000); // DELAY DE 5 SEGUNDOS
  
  lcd.noBacklight(); // DESLIGA A ILUMINAÇÃO DO DISPLAY
  delay(2000); // DELAY DE 2 SEGUNDOS
  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY
  delay(2000); // DELAY DE 2 SEGUNDOS
  
  lcd.clear(); // LIMPA O DISPLAY
  //lcd.noBacklight(); // DESLIGA A ILUMINAÇÃO DO DISPLAY
}

void loop() {

  //lcd.clear();
  lcd.setCursor(0, 0); // VOLTA PARA A LINHA 1: SEM ISSO, O TEXTO SEGUIRIA DO FIM DA LINHA 2
  lcd.print("- Ola, Mundo! -");
  lcd.setCursor(0, 1); // POSICIONA O CURSOR NA PRIMEIRA COLUNA DA LINHA 2
  lcd.print("Fim do Setup ()");

}
