#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H
#include <ArduinoBLE.h>

void initBLE();
void sendButtonCommand(uint8_t id, uint8_t action);
void checkBLEEvents();
bool isBLEConnected();

#endif