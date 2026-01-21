#include "Config.h"
#include "Peripherals.h"
#include "BleManager.h"

unsigned long lastActionTime = 0;

void setup() {
  Serial.begin(115200);
  
  initPeripherals();
  initBLE();        
  
  lastActionTime = millis();
}

void loop() {
  checkBLEEvents(); 
  
  int btnIndex = checkButtons(); // 버튼 확인
  
  if (btnIndex != -1) {
    lastActionTime = millis(); // 타이머 리셋
    
    if (btnIndex == 4) { // Laser
        controlLaser(true);
    } else {
        sendButtonCommand(btnIndex, 1);
    }
  } 
  else {
    controlLaser(false); // 버튼 안 누르면 끄기
  }
}