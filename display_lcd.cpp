/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
**************************
* @file    display_lcd.cpp
* @brief   Implementação das funções de inicialização do display LCD I2C.
**************************
* Date:     21/05/2026
* Author:   Julio Cesar Piva
* email:    juliopiva11@gmail.com
* Project:  Maquina_Ferramentas
* Version:  1.0
**************************
*/

#include "display_lcd.h"

/*
**********************
* @name   initLCD
* @brief  Inicializa o display LCD e habilita a retroiluminação.
**********************
* @input: lcd - Ponteiro para o objeto LiquidCrystal_I2C.
* @return: sem retorno
*/
void initLCD(LiquidCrystal_I2C *lcd)
{
    if (lcd != NULL)
    {
        lcd->init();
        lcd->backlight();
    }
}

