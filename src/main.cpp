#include <Arduino.h>
#include "Config.h"
#include "Peripherals.h"
#include "BleManager.h"

unsigned long lastActionTime = 0;

void setup() {
  Serial.begin(115200);
  
  Serial.println("System Starting...");

  initPeripherals(); // 하드웨어(버튼, 레이저) 초기화
  initBLE();         // BLE 초기화
  
  lastActionTime = millis();
}

void loop() {
  checkBLEEvents();
  
  int btnIndex = checkButtons(); // 눌린 버튼 번호 반환 (없으면 -1), 버튼 상태 확인

  if (btnIndex != -1) {
    lastActionTime = millis(); // 버튼 누르면 타이머 리셋

    if (btnIndex == 4) {
        controlLaser(true);
    } else {
        // 레이저 외 버튼은 BLE 명령 전송
        sendButtonCommand(btnIndex, 1); 
    }
  } else {
    controlLaser(false); 
  }

  if (millis() - lastActionTime > SLEEP_TIMEOUT) {
    Serial.println("Timeout! Entering Deep Sleep...");
    
    enterDeepSleep(); 
  }
}