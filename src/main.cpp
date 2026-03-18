#include <Arduino.h>
#include "Config.h"
#include "Peripherals.h"
#include "BleManager.h"

unsigned long lastActionTime = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("System Starting...");

  initPeripherals();
  initBLE();
}

void loop() {
  checkBLEEvents();
  
  int btnIndex = checkButtons(); // 눌린 버튼 번호 반환 (없으면 -1), 버튼 상태 확인

  if (btnIndex != -1) {
    if (btnIndex == 4) {
      // 레이저
        controlLaser(true);
    } else {
        // BLE 명령 전송
        sendButtonCommand(btnIndex, 1); 
    }
  } else {
    controlLaser(false); 
  }
}