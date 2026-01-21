#include "Peripherals.h"
#include "Config.h"

const int buttonPins[] = {PIN_BTN_POWER, PIN_BTN_PRE, PIN_BTN_NEXT, PIN_BTN_PLAY, PIN_BTN_LASER};

void initPeripherals() {
  for (int i = 0; i < 5; i++) pinMode(buttonPins[i], INPUT_PULLUP);
  pinMode(PIN_LASER, OUTPUT);
  pinMode(PIN_VIBRATION, OUTPUT);
}

void controlLaser(bool state) {
  digitalWrite(PIN_LASER, state ? HIGH : LOW);
}


void enterDeepSleep(){
  controlLaser(false);
  digitalWrite(PIN_VIBRATION, LOW);
  esp_sleep_enable_ext0_wakeup((gpio_num_t)D2, 0);

  esp_deep_sleep_start();
}