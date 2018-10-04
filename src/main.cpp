#include <Arduino.h>
#include "classes/clsSpeedServo.h"

clsSpeedServo srv01(8);
clsSpeedServo srv02(9);
clsSpeedServo srv03(10);
clsSpeedServo srv04(12);

/*
    Controle da garra
*/
// #define HAL_GARRA_DC_A  22
// #define HAL_GARRA_DC_B  23
// #define HAL_GARRA_DC_E  25

// bool garraAberta = true;

// void garra_init(){
//     pinMode(HAL_GARRA_DC_A, OUTPUT);
//     pinMode(HAL_GARRA_DC_B, OUTPUT);
//     pinMode(HAL_GARRA_DC_E, OUTPUT);

//     digitalWrite(HAL_GARRA_DC_A, LOW);
//     digitalWrite(HAL_GARRA_DC_B, LOW);
//     digitalWrite(HAL_GARRA_DC_E, LOW);
// }

// void garra_abrir(){
//     if (!garraAberta){
//         digitalWrite(HAL_GARRA_DC_A, HIGH);
//         digitalWrite(HAL_GARRA_DC_B, LOW);
        
//         digitalWrite(HAL_GARRA_DC_E, HIGH);
//         delay(1500);
//         garraAberta = true;
//         digitalWrite(HAL_GARRA_DC_E, LOW);
//     }
// }

// void garra_fechar(){
//     if (garraAberta){
//         digitalWrite(HAL_GARRA_DC_A, LOW);
//         digitalWrite(HAL_GARRA_DC_B, HIGH);
        
//         digitalWrite(HAL_GARRA_DC_E, HIGH);
//         delay(1500);
//         garraAberta = false;
//         digitalWrite(HAL_GARRA_DC_E, LOW);
//     }
// }

/*
    Rotinas de controle dos servos
*/

void loopInterno()
{
    srv01.tick();
    srv02.tick();
    srv03.tick();
    srv04.tick();
}

void setup()
{
    SS_setFuncaoLoop(loopInterno);
    srv03.turnOnComplementary(11);

    srv01.write(0);

    delay(5000);
    
    while (1)
    {
        srv01.write(0);
        srv02.write(180);
        srv03.write(180);
        srv04.write(180);

        srv02.wait();
        srv03.wait();
        srv04.wait();
        
        delay(5000);
        
        srv02.write(130);
        srv03.write(110);
        srv04.write(0);

        srv02.wait();
        srv03.wait();
        srv04.wait();

        srv03.write(40);
        srv01.write(10);
        srv03.wait();

        delay(2000);
        
    }
}

void loop()
{
    loopInterno();
}