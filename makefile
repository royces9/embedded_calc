BOARD_TAG    = mega
BOARD_SUB    = atmega2560
MONITOR_PORT = /dev/ttyACM0
ARDUINO_DIR  = /usr/share/arduino/
ARDMK_VENDOR = archlinux-arduino/
ARDMK_DIR = /usr/share/arduino/
AVR_TOOLS_DIR = /usr
ARDUINO_LIBS = SoftwareSerial Wire SPI HID EEPROM
AVRDUDE = /usr/bin/avrdude
AVRDUDE_CONF = /etc/avrdude.conf

include /usr/share/arduino/Arduino.mk


