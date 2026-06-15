/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
**************************
* @file    maquina_ferramentas.h
* @brief   Declaração da classe responsável pelo controle da máquina dispensadora de ferramentas.
**************************
* Date:     21/05/2026
* Author:   Julio Cesar Piva
* email:    juliopiva11@gmail.com
* Project:  Maquina_Ferramentas
* Version:  1.0
**************************
*/

#ifndef MAQUINA_FERRAMENTAS_H
#define MAQUINA_FERRAMENTAS_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

class MaquinaFerramentas {
private:
    LiquidCrystal_I2C *lcd;
    Keypad *keypad;
    int motorPins[100];
    String produtos[100];

    /*
    **********************
    * @name   acionarMotor
    * @brief  Aciona o motor correspondente ao produto selecionado.
    **********************
    * @input: indice - Índice do produto a ser dispensado.
    * @return: sem retorno
    */
    void acionarMotor(int indice);

public:

    /*
    **********************
    * @name   MaquinaFerramentas
    * @brief  Construtor da classe MaquinaFerramentas.
    **********************
    * @input: lcd_param - Ponteiro para o display LCD.
    * @input: keypad_param - Ponteiro para o teclado matricial.
    * @return: sem retorno
    */
    MaquinaFerramentas(LiquidCrystal_I2C *lcd_param, Keypad *keypad_param);

    /*
    **********************
    * @name   inicializarEstoque
    * @brief  Inicializa os produtos, pinos dos motores e periféricos da máquina.
    **********************
    * @input: sem parâmetros.
    * @return: sem retorno
    */
    void inicializarEstoque();

    /*
    **********************
    * @name   loopMaquina
    * @brief  Executa continuamente a lógica de operação da máquina dispensadora.
    **********************
    * @input: sem parâmetros.
    * @return: sem retorno
    */
    void loopMaquina();
    void mostrarMensagemInicial();
};

#endif // MAQUINA_FERRAMENTAS_H
