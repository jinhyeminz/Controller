#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#include <Arduino.h>

void initPeripherals();
int checkButtons();

void controlLaser(bool state);
void controlVibration(bool state);

#endif