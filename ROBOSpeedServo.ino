#include <Arduino.h>
#include "clsSpeedServo.h"

clsSpeedServo srv01(8);
clsSpeedServo srv02(9);
clsSpeedServo srv03(10);
clsSpeedServo srv04(12);

void iniciaServos(){
    /*
    Função que serve para iniciar os servos.

    Use esta função para definir as posições iniciais dos servos.
    */

   /*
    Função que liga o pino 11 como servo complementar do srv03.
    Servo complementar irá sempre movimentar com um angulo 180 - alpha.

    Isto é, se for solicitado que o srv03 vá para  posição 45, o servo complementar (pino 11) irá para a posição 180 - 45 = 135.
   */
    srv03.turnOnComplementary(11);

    /*
        Ajusta posição inicial do srv01 para o angulo 0.
    */
    srv01.write(0);

    // Apenas para caracteriar o sistema.
    delay(5000);
}

/*
    Para cada servo criado, crie um comando, conforme exemplo.
*/
void rotinaTick(){
    srv01.tick();
    srv02.tick();
    srv03.tick();
    srv04.tick();
}

/*
    Esta rotina será executada continuamente.
    Ela é responsável por definir qual o movimento que o robo irá fazer.

    Quando o comando srv0x.wait(); for chamando, a rotina não irá continuar até que o servo srv0x conclua seu movimento. Enquanto ele espera, os outros servos podem movimentar livremente.
*/
void rotinaServo(){
    srv01.write(0);
    srv02.write(180);
    srv03.write(180);
    srv04.write(180);

    srv01.setTempo(5); // use para definir um tempo de 5ms entre cada passo de Delta graus do motor
    srv01.setDelta(3); // define um passo do servo como 3 graus.

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

/*
    Rotinas de controle dos servos

    Cuidado ao alterar sem o devido conhecimento.
*/
void setup()
{
    SS_setFuncaoLoop(rotinaTick);
    iniciaServos();
    
    while (1)
    {
        rotinaServo();        
    }
}

void loop()
{
    rotinaTick();
}