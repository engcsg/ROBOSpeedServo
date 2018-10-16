
#if !defined(_CLS_FUNC_TIMER_H_)
#define _CLS_FUNC_TIMER_H_


#include "Arduino.h"

typedef void (*FuncaoTick)(void);

class clsFuncTimer
{
  private:
    bool _bAtivo = false;
    long _lUltimoMillis = 0;
    long _iIntervalo = 1000;
    FuncaoTick _aFuncaoExterna = nullptr;

    void _callExternalFunc(void);

  public:
    clsFuncTimer(bool timerAtivo, unsigned int intervalo);
    ~clsFuncTimer();

    void startTimer(void);
    void stopTimer(void);

    bool getTimerStatus(void);

    unsigned int getInterval(void);
    void setInterval(unsigned int aNewInterval);

    void setFuncaoExterna(FuncaoTick aFuncao);
    void clearFuncaoExterna(void);

    void tick();
};
/*
    Implementação da classe
    =====================================================================
*/
clsFuncTimer::clsFuncTimer(bool timerAtivo, unsigned int intervalo)
{
    this->_bAtivo = timerAtivo;
    this->_iIntervalo = intervalo;
}

clsFuncTimer::~clsFuncTimer()
{
}

void clsFuncTimer::_callExternalFunc(){
    if (this->_aFuncaoExterna != nullptr){
        this->_aFuncaoExterna();
    }
}

void clsFuncTimer::startTimer(void){
    this->_bAtivo = true;
}

void clsFuncTimer::stopTimer(void){
    this->_bAtivo = false;
}

bool clsFuncTimer::getTimerStatus(void){
    return this->_bAtivo;
}

unsigned int clsFuncTimer::getInterval(void){
    return this->_iIntervalo;
}

void clsFuncTimer::setInterval(unsigned int aNewInterval){
    this->_iIntervalo = aNewInterval;
}

void clsFuncTimer::setFuncaoExterna(FuncaoTick aFuncao){
    this->_aFuncaoExterna = aFuncao;
}

void clsFuncTimer::clearFuncaoExterna(void){
    this->_aFuncaoExterna = nullptr;
}

void clsFuncTimer::tick(){
    long duracao = millis() - this->_lUltimoMillis;
    if ((this->_bAtivo) and (duracao >= this->_iIntervalo)){
        this->_callExternalFunc();
        this->_lUltimoMillis = millis();
    }
}

#endif // _CLS_FUNC_TIMER_H_
