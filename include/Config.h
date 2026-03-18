#ifndef CONFIG_H
#define CONFIG_H


// Power, Pre, Next, Play, Laser
const int buttonPins[5] = {D2, D3, D4, D5, D6};
const uint8_t BUTTON_IDS[5] = {0x01, 0x02, 0x03, 0x04, 0x05};

#define PIN_VIBRATION       D7
#define PIN_LASER           D8

#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHAR_UUID           "abcdefab-1234-1234-1234-abcdefabcdef"

#define DEBOUNCE_DELAY  30

#endif