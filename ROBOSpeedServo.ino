#include <Arduino.h>
#include "clsSpeedServo.h"

clsSpeedServo srv01(8);
clsSpeedServo srv02(9);
clsSpeedServo srv03(10);
clsSpeedServo srv04(12);

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