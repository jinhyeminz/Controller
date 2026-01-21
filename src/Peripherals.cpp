#include "Peripherals.h"
#include "Config.h"

unsigned long lastDebounceTime = 0;
int lastButtonState = HIGH;

void initPeripherals() {
  for (int i = 0; i < 5; i++) pinMode(buttonPins[i], INPUT_PULLUP);
  pinMode(PIN_VIBRATION, OUTPUT);
  pinMode(PIN_LASER, OUTPUT);

  digitalWrite(PIN_LASER, LOW);
  digitalWrite(PIN_VIBRATION, LOW);
}

int checkButtons() {
    for (int i = 0; i < 5; i++) {
        int reading = digitalRead(buttonPins[i]);
        
        if (reading == LOW) { // 버튼 눌림
            // loop가 빠르기 때문에 non-blocking 방식이 좋지만 간단 구현을 위해 delay 사용
            delay(DEBOUNCE_DELAY);
            if (digitalRead(buttonPins[i]) == LOW) {
                return i; // 눌린 버튼 인덱스 반환
            }
        }
    }
    return -1; // 아무것도 안 눌림
}

void controlLaser(bool state) {
  digitalWrite(PIN_LASER, state ? HIGH : LOW);
}

void controlVibration(bool state) {
    digitalWrite(PIN_VIBRATION, state ? HIGH : LOW);
}


void enterDeepSleep(){
  
  controlLaser(false);
  controlVibration(false);
  digitalWrite(PIN_VIBRATION, LOW);

  // 깨어날 조건, Power 버튼 -> LOW
  esp_sleep_enable_ext0_wakeup((gpio_num_t)D2, 0);
  
  // 딥슬립 모드
  esp_deep_sleep_start();
}