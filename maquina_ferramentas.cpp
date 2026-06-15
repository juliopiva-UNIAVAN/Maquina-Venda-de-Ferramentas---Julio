/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
**************************
* @file    maquina_ferramentas.cpp
* @brief   Implementação das funções da classe MaquinaFerramentas.
**************************
* Date:     21/05/2026
* Author:   Julio Cesar Piva
* email:    juliopiva11@gmail.com
* Project:  Maquina_Ferramentas
* Version:  1.0
**************************
*/

#include "maquina_ferramentas.h"

// Pino do motor DC
const int motorDC = 8;
// Pino do switch de estoque (fim de curso)
const int Out1 = 30; 
// LED indicador de DISPENSADO
const int ledDispensado = 31; 
// LED indicador de SEM ESTOQUE
const int ledSemEstoque = 32; 
// Sensor de barreira (queda da ferramenta)
const int sensorQueda = 33;

/*
**********************
* @name   MaquinaFerramentas
* @brief  Construtor da classe MaquinaFerramentas.
*********************
* @input: lcd_param - Ponteiro para o display LCD.
* @input: keypad_param - Ponteiro para o teclado matricial.
* @return: sem retorno
*/
MaquinaFerramentas::MaquinaFerramentas(LiquidCrystal_I2C *lcd_param, Keypad *keypad_param) {
    lcd = lcd_param;
    keypad = keypad_param;
}

/*
**********************
* @name   inicializarEstoque
* @brief  Inicializa os produtos, configura os pinos, sensores, LEDs e prepara a interface da máquina.
*********************
* @input: sem parâmetros.
* @return: sem retorno
*/
void MaquinaFerramentas::inicializarEstoque() {
    String listaProdutos[100] = {
        "Martelo","Alicate","Chave Fenda","Chave Philips","Serrote","Trena","Nivel","Parafusadeira","Broca","Lixa",
        "Chave Inglesa","Chave Allen","Grifo","Torquimetro","Cortador","Estilete","Tesoura","Pinca","Saca Prego","Formao",
        "Marreta","Talhadeira","Espatula","Rolo Pintura","Pincel","Balde","Luvas","Mascara","Capacete","Oculos",
        "Parafuso","Porca","Arruela","Bucha","Prego","Tarraxa","Rebite","Grampo","Abraçadeira","Fita Isolante",
        "Fita Crepe","Fita Dupla","Cola Madeira","Cola Epoxi","Cola Instant","Silicone","Vedante","Graxa","Lubrificante","Spray WD40",
        "Multimetro","Teste Voltagem","Lanterna","Lampada","Tomada","Plug","Extensao","Adaptador","Disjuntor","Fusivel",
        "Cabo Eletrico","Cabo Rede","Cabo HDMI","Cabo USB","Cabo P2","Cabo P10","Cabo Coaxial","Conector","Terminal","Chave Teste",
        "Escada","Banco","Carrinho","Caixa Ferram","Bolsa Ferram","Organizador","Prateleira","Suporte","Gancho","Cavalete",
        "Serra Copo","Serra Tico","Serra Circular","Disco Corte","Disco Lixa","Disco Diamante","Broca Aço","Broca Concr","Broca Madeira","Broca Vidro",
        "Pistola Cola","Pistola Pint","Compressor","Mangueira","Bomba Agua","Bomba Ar","Medidor Press","Manometro","Termometro","Detector"
    };

    for (int i = 0; i < 100; i++) {
        motorPins[i] = 9 + (i % 4); 
        produtos[i] = listaProdutos[i];
        pinMode(motorPins[i], OUTPUT);
        digitalWrite(motorPins[i], LOW);
    }

    pinMode(motorDC, OUTPUT);
    digitalWrite(motorDC, LOW);

    pinMode(Out1, INPUT_PULLUP);

    pinMode(ledDispensado, OUTPUT);
    digitalWrite(ledDispensado, LOW);

    pinMode(ledSemEstoque, OUTPUT);
    digitalWrite(ledSemEstoque, LOW);

    pinMode(sensorQueda, INPUT_PULLUP);

    // Já inicia direto na tela de seleção
    lcd->clear();
    lcd->setCursor(0,0);
    lcd->print("Linha:_");
    lcd->setCursor(0,1);
    lcd->print("Coluna:_");
}

/*
**********************
* @name   acionarMotor
* @brief  Aciona o motor correspondente ao produto selecionado e aguarda a confirmação do sensor de queda para finalizar a dispensação.
*********************
* @input: indice - Índice do produto a ser dispensado.
* @return: sem retorno
*/
void MaquinaFerramentas::acionarMotor(int indice) {

    // Liga o motor correspondente
    digitalWrite(motorPins[indice], HIGH);
    digitalWrite(motorDC, HIGH);

    // Aguarda o sensor detectar a queda
    while (digitalRead(sensorQueda) == LOW) {
        // Espera o item cair
    }

    // Sensor detectou a queda
    digitalWrite(ledDispensado, HIGH);

    // Desliga o motor correspondente
    digitalWrite(motorPins[indice], LOW);
    digitalWrite(motorDC, LOW);
}

/*
**********************
* @name   loopMaquina
* @brief  Executa continuamente a lógica da máquina, realizando a seleção do produto, verificação de estoque e confirmação da dispensação através do sensor de queda.
*********************
* @input: sem parâmetros.
* @return: sem retorno
*/
void MaquinaFerramentas::loopMaquina() {
    static String entrada = "";
    static int etapa = 0;
    static int linha = -1;
    static int coluna = -1;

    char key = keypad->getKey();

    if (!key) return;

    if ((etapa == 0 || etapa == 1) &&
        (key == 'A' || key == 'B' || key == 'C' || key == 'D')) {

        lcd->clear();
        lcd->setCursor(0,0);
        lcd->print("Tecla invalida");

        delay(1000);

        lcd->clear();
        lcd->setCursor(0,0);
        lcd->print("Linha:_");
        lcd->setCursor(0,1);
        lcd->print("Coluna:_");

        etapa = 0;
        entrada = "";

        return;
    }

    if (key == '*') {

        entrada = "";
        etapa = 0;
        linha = -1;
        coluna = -1;

        lcd->clear();
        lcd->setCursor(0,0);
        lcd->print("Linha:_");
        lcd->setCursor(0,1);
        lcd->print("Coluna:_");

        return;
    }

if (key == '#') {

    if (etapa == 1 && coluna != -1) {

        int indice = (linha * 10) + coluna;

        // Tela de liberando produto
        lcd->clear();
        lcd->setCursor(0,0);
        lcd->print("Liberando");

        lcd->setCursor(0,1);
        lcd->print(produtos[indice].substring(0,16));

        delay(1500);

        // Verifica se existe estoque
        if (digitalRead(Out1) == HIGH) {

            // Liga o motor correspondente e aguarda o sensor
            acionarMotor(indice);

            // Mostra confirmação da dispensação
            lcd->clear();
            lcd->setCursor(0,0);
            lcd->print("Dispensado!");

            // Mantém o LED verde aceso por mais 1 segundo
            delay(1000);

            digitalWrite(ledDispensado, LOW);

        } else {

            // Sem estoque
            lcd->clear();
            lcd->setCursor(0,0);
            lcd->print("Sem estoque!");

            digitalWrite(ledSemEstoque, HIGH);

            delay(2000);

            digitalWrite(ledSemEstoque, LOW);
        }

        // Volta para a tela inicial
        lcd->clear();
        lcd->setCursor(0,0);
        lcd->print("Linha:_");

        lcd->setCursor(0,1);
        lcd->print("Coluna:_");

        etapa = 0;
        entrada = "";
        linha = -1;
        coluna = -1;
    }

    return;
}
    entrada += key;

    if (etapa == 0) {

        linha = entrada.charAt(0) - '0';
        etapa = 1;

        lcd->clear();
        lcd->setCursor(0,0);
        lcd->print("Linha: ");
        lcd->print(linha);

        lcd->setCursor(0,1);
        lcd->print("Coluna:_");

        entrada = "";

    } else if (etapa == 1) {

        coluna = entrada.charAt(0) - '0';

        lcd->clear();
        lcd->setCursor(0,0);
        lcd->print("Confirma L");
        lcd->print(linha);
        lcd->print("C");
        lcd->print(coluna);

        lcd->setCursor(0,1);
        lcd->print("# para confirmar");
    }
}
