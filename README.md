### 프로젝트 구조

---

 ESP32-BLE-Remote

┣ include             # 헤더 (설정 및 선언)

┃ ┣ Config.h          # 핀 번호, UUID, 타임아웃 설정

┃ ┣ BleManager.h      # BLE 통신 인터페이스

┃ ┗ Peripherals.h     # 하드웨어 제어 인터페이스

┣ src                 # 소스 (구현)

┃ ┣ main.cpp          # 메인 로직 (이벤트 루프)

┃ ┣ BleManager.cpp    # BLE 데이터 송수신 구현

┃ ┗ Peripherals.cpp   # GPIO, 디바운싱, Deep Sleep 구현

┗ platformio.ini      # PlatformIO 설정
