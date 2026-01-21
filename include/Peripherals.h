#ifndef PERIPHERALS_H
#define PERIPHERALS_H
#include <Arduino.h>

void initPeripherals();
void controlLaser(bool state);
void controlVibration(bool state);
int checkButtons(); // 눌린 버튼 인덱스 반환 없으면 -1
void enterDeepSleep();

#endif