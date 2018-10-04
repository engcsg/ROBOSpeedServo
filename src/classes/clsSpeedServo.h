
#if !defined(CLS_SPEED_SERVO_H_)
#define CLS_SPEED_SERVO_H_

#include "Arduino.h"
#include <Servo.h>

#define PROCSERVO_ERRO_TOLERANCIA 2

typedef void (*FuncaoLoop)(void);
FuncaoLoop aFuncaoLoop = nullptr;

void SS_setFuncaoLoop(FuncaoLoop aNewFuncLoop){
    aFuncaoLoop = aNewFuncLoop;
}

void SS_clearFuncaoLoop(){
    aFuncaoLoop = nullptr;
}

void SS_callLoop(){
    if (aFuncaoLoop != nullptr){
        aFuncaoLoop();
    }
}

class clsSpeedServo
{
private:
    Servo aServo;
    Servo aServoB;
    int posDestino;
    int delta;
    int tempo;
    long ultimoCheck;

    int getError();
public:
    clsSpeedServo(unsigned int aPin);
    ~clsSpeedServo();

    void turnOnComplementary(unsigned int aPin);
    void tick();

    void write(int);
    
    void setDelta(int);
    int getDelta();

    void setTempo(int);
    int getTempo();

    void wait();
};

void clsSpeedServo::wait(){
    while(abs(this->getError()) > PROCSERVO_ERRO_TOLERANCIA){
        SS_callLoop();
        delay(5);
    }
}

void clsSpeedServo::write(int aNewPos){
    this->posDestino = aNewPos;
}

void clsSpeedServo::setDelta(int aNewDelta){
    this->delta = aNewDelta;
}

int clsSpeedServo::getDelta(){
    return this->delta;
}

void clsSpeedServo::setTempo(int aNewTempo){
    this->tempo = aNewTempo;
}

int clsSpeedServo::getTempo(){
    return this->tempo;
}

clsSpeedServo::clsSpeedServo(unsigned int aPin)
{
    this->delta = 3;
    this->tempo = 125;
    this->aServo.attach(aPin);
}

clsSpeedServo::~clsSpeedServo()
{
    this->aServo.detach();
    if (this->aServoB.attached()){
        this->aServoB.detach();
    }
}

void clsSpeedServo::turnOnComplementary(unsigned int aPin){
    this->aServoB.attach(aPin);
}

int clsSpeedServo::getError(){
    int iNovaPos = this->aServo.read();
    int iPosDestino = this->posDestino;
    
    return (iPosDestino - iNovaPos);
}

void clsSpeedServo::tick(){
    
    int iNovaPos = this->aServo.read();
    int iPosDestino = this->posDestino;
    
    int erro = iPosDestino - iNovaPos;
    
    if (abs(erro) > PROCSERVO_ERRO_TOLERANCIA) {
        
        long duracao = millis() - this->ultimoCheck;
        
        if (duracao >= this->tempo) {
            // deve processar o passo a ser feito.
            if (erro > 0) {
                // deve avançar
                if (abs(erro) > this->delta) {
                    iNovaPos = iNovaPos + this->delta;
                } else {
                    iNovaPos = iNovaPos + abs(erro);
                }
            } else {
                // deve recuar
                if (abs(erro) > this->delta) {
                    iNovaPos = iNovaPos - this->delta;
                } else {
                    iNovaPos = iNovaPos - abs(erro);
                }
            }
        
            this->aServo.write(iNovaPos);
            if (this->aServoB.attached()){
                this->aServoB.write(180 - iNovaPos);
            }
            
            this->ultimoCheck = millis();
        } 
    }
}


#endif // CLS_SPEED_SERVO_H_
