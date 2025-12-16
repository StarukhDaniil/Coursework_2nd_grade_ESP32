#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <esp32-hal-timer.h>
#include <ESP32SPISlave.h>
#include <Ticker.h>
#include "hall_signal.h"
#include "main_helper.h"
#include "bluetoothmanager.h"
#include "blebuff_service.h"

HallSignal hall_signal;
ESP32SPISlave spi2Slave;
BLEBuff_Service BBuffService(hall_signal);

Ticker thresholdUpd_ticker;

uint8_t SPI2_RxBuff[RX_DATA_BUFF_SIZE] = {0};

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

MyServerCallbacks g_serverCallbacks;
MyCharacteristicCallbacks g_charCallbacks;

void setup() {
    pinMode(23, OUTPUT);
    setup_spi2();
    thresholdUpd_ticker.attach(1.0, updateThreshold_wrapper);
    setupBLE();
    Serial.begin(115200);
}

void loop() {
    if (spi2Slave.remained() == 0 && spi2Slave.available() == 0) {
        spi2Slave.queue(SPI2_RxBuff, NULL, RX_DATA_BUFF_SIZE);
    }

    if (spi2Slave.available()) {
        // pointer for reading buffer as uint16_t
        uint16_t* pRxBuff = reinterpret_cast<uint16_t*>(SPI2_RxBuff);

        hall_signal.add_values(pRxBuff, RSLTS_PER_PCKT);

        if (hall_signal.info() & SIGNAL_VALUE) {
            digitalWrite(23, HIGH);
        }
        else {
            digitalWrite(23, LOW);
        }

        BBuffService.handleNewData();

        spi2Slave.pop();
    }
}