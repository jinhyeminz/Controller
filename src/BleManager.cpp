#include "Config.h"
#include "Peripherals.h"
#include "BleManager.h"

unsigned long lastActionTime = 0;

void setup() {
  Serial.begin(115200);
  
  initPeripherals(); // 하드웨어 초기화
  initBLE();         // BLE 초기화
  
  lastActionTime = millis();
}

void loop() {
  checkBLEEvents(); // BLE 이벤트 처리
  
  int btnIndex = checkButtons(); // 버튼 확인
  
  if (btnIndex != -1) {
    lastActionTime = millis(); // 타이머 리셋
    
    // 로직 처리
    if (btnIndex == 4) { // Laser
        controlLaser(true);
    } else {
        sendButtonCommand(btnIndex, 1);
    }
  } else {
    controlLaser(false); // 버튼 안 누르면 끄기
  }

  // 슬립 모드 체크 로직...
}