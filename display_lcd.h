/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
**************************
* @file    display_lcd.h
* @brief   Declaração das funções de inicialização do display LCD I2C.
**************************
* Date:     21/05/2026
* Author:   Julio Cesar Piva
* email:    juliopiva11@gmail.com
* Project:  Maquina_Ferramentas
* Version:  1.0
**************************
*/

#ifndef DISPLAY_LCD_H
#define DISPLAY_LCD_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*
**********************
* @name   initLCD
* @brief  Inicializa um display LCD I2C específico.
**********************
* @input: lcd - Ponteiro para o objeto LiquidCrystal_I2C.
* @return: sem retorno
*/
void initLCD(LiquidCrystal_I2C *lcd);

#endif // DISPLAY_LCD_H

