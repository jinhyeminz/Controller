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
  // 1. BLE 이벤트 처리 (연결 유지 및 데이터 수신)
  checkBLEEvents();
  
  // 2. 버튼 상태 확인
  int btnIndex = checkButtons(); // 눌린 버튼 번호 반환 (없으면 -1)
  
  if (btnIndex != -1) {
    lastActionTime = millis(); // 버튼 누르면 타이머 리셋
    
    // 로직 처리
    if (btnIndex == 4) { // 4번은 레이저 버튼 (Config.h에 정의된 순서 확인)
        controlLaser(true);
    } else {
        // 레이저 외의 버튼은 BLE 명령 전송
        sendButtonCommand(btnIndex, 1); 
    }
  } else {
    controlLaser(false); // 버튼 안 누르고 있으면 레이저 끄기
  }

  // 3. 딥 슬립(절전) 체크 로직
  // Config.h에 SLEEP_TIMEOUT (예: 10000ms) 정의되어 있어야 함
  if (millis() - lastActionTime > SLEEP_TIMEOUT) {
    Serial.println("Timeout! Entering Deep Sleep...");
    
    // BLE 종료 등 정리 작업 (BleManager.cpp에 이 함수가 있으면 좋음, 없으면 생략 가능)
    // stopBLE(); 
    
    // Peripherals.cpp에 만들어둔 슬립 함수 호출
    enterDeepSleep(); 
  }
}