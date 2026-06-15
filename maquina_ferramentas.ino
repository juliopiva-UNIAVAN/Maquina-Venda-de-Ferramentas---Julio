/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
**************************
* @file    maquina_ferramentas.ino
* @brief   Arquivo principal da máquina dispensadora de ferramentas.
**************************
* Date:     21/05/2026
* Author:   Julio Cesar Piva
* email:    juliopiva11@gmail.com
* Project:  Maquina_Ferramentas
* Version:  1.0
**************************
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#include "display_lcd.h"
#include "maquina_ferramentas.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Teclado 4x4
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

MaquinaFerramentas maquina(&lcd, &keypad);

/*
**********************
* @name   setup
* @brief  Inicializa os periféricos e prepara a máquina para operação.
**********************
* @input: sem parâmetros.
* @return: sem retorno
*/
void setup() {
    initLCD(&lcd);
    maquina.inicializarEstoque();
}

/*
**********************
* @name   loop
* @brief  Executa continuamente a lógica principal da máquina dispensadora.
**********************
* @input: sem parâmetros.
* @return: sem retorno
*/
void loop() {
    maquina.loopMaquina();
}

