#include "Peripherals.h"
#include "Config.h"

unsigned long lastDebounceTime[5] = {0, 0, 0, 0, 0};
int lastButtonState[5] = {HIGH, HIGH, HIGH, HIGH, HIGH};
int buttonStates[5] = {HIGH, HIGH, HIGH, HIGH, HIGH};

void initPeripherals() {
  for (int i = 0; i < 5; i++){
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  
  pinMode(PIN_VIBRATION, OUTPUT);
  pinMode(PIN_LASER, OUTPUT);

  digitalWrite(PIN_VIBRATION, LOW);
  digitalWrite(PIN_LASER, LOW);
}

int checkButtons() {
    unsigned long currentTime = millis();
    for (int i = 0; i < 5; i++) {
        int reading = digitalRead(buttonPins[i]);
        
        if (reading != lastButtonState[i]) { // 버튼 눌림 -> 디바운스 타이머 갱신
            lastDebounceTimes[i] = currentTime;
            lastButtonStates[i] = reading;
        }

        if((currentTime - lastDebounceTime[i]) > DEBOUNCE_DELAY){
            if(reading != buttonStates[i]){
                buttonStates[i] = reading;

                if(buttonStates[i] == LOW){
                    return i;
                }
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