#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H
#include <ArduinoBLE.h>

void initBLE();
void sendButtonCommand(int buttonIndex, int action);
void checkBLEEvents();
bool isBLEConnected();

#endif  