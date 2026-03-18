#include "BleManager.h"
#include "Config.h"
#include "Peripherals.h" // 진동 제어를 위해 필요
#include <ArduinoBLE.h>

BLEService presenterService(SERVICE_UUID);
BLECharacteristic buttonCharacteristic(CHAR_UUID, BLERead | BLENotify | BLEWrite, 40);

bool isPlaying = false; // 재생 상태 토글용

// 수신 콜백 함수
void onBLEWrite(BLEDevice central, BLECharacteristic characteristic);

void initBLE() {
    if (!BLE.begin()) {
        Serial.println("Starting BLE failed!");
        while (1);
    }

    BLE.setLocalName("ESP32");
    BLE.setAdvertisedService(presenterService);
    
    buttonCharacteristic.setEventHandler(BLEWritten, onBLEWrite);
    presenterService.addCharacteristic(buttonCharacteristic);
    
    BLE.addService(presenterService);
    BLE.advertise();
    
    Serial.println("BLE Initialized & Advertising...");
}

void checkBLEEvents() {
    BLE.poll(); // BLE 이벤트 처리
}

bool isBLEConnected() {
    BLEDevice central = BLE.central();
    return (central && central.connected());
}

void sendButtonCommand(int buttonIndex, int action) {
    if (!isBLEConnected()) return;

    uint8_t packet[2];
    packet[0] = BUTTON_IDS[buttonIndex];
    packet[1] = 0x01; // 기본 클릭

    // Play/Pause 버튼(인덱스 3)은 토글 처리
    if (buttonIndex == 3) {
        isPlaying = !isPlaying;
        packet[1] = isPlaying ? 0x01 : 0x02;
    }

    buttonCharacteristic.writeValue(packet, 2);
}

// 진동모터 값 받는 함수
void onBLEWrite(BLEDevice central, BLECharacteristic characteristic) {
    uint8_t buffer[2];
    int length = characteristic.readValue(buffer, sizeof(buffer));

    if (length == 2 && buffer[0] == 0x06) { // 진동 명령
        controlVibration(buffer[1] == 0x01);
    }
}