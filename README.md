# ROBOSpeedServo
Arduino Due Class to control ServoMotors with threading and speed control.
Classe para controlar servo-motores com suporte para threads e controle de velocidade.

## Releases
Download releases deste código em: https://github.com/engcsg/ROBOSpeedServo/releases

## Compatibilidade
Compatível e testado com o Arduino Due e com 4 servo-motores simultâneos.
Não foi testado com nenhum outro Arduino.

## Orientações Gerais

### clsFuncTimer.h
Classe criada para ser um timer que dispara uma função específica após determinado tempo.
Esta classe é necessária para o sistema funcionar.

### clsSpeedServo.h
Classe principal que é responsável pelo controle dos motores.

### ROBOSpeedServo.ino
Sketch do arduino - exemplo - de criação de rotina operacional do robo usando servos.
