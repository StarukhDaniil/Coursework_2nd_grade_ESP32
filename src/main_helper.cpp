#include "main_helper.h"
#include "hall_signal.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "main_instances.h"

#define BYTES_PER_BLE_PCKT 200

void setup_spi2() {
    spi2Slave.begin(VSPI, SPI2_CLK, SPI2_MISO, SPI2_MOSI, SPI2_SS);
    spi2Slave.setDataMode(SPI_MODE0);
}

void sendData(uint8_t* data, size_t size) {
    Serial.println("sending data");

    if (!deviceConnected) {
        return;
    }

    if (size > BYTES_PER_BLE_PCKT) {
        for (size_t i = 0; i < size; i += BYTES_PER_BLE_PCKT) {
            if (size - i <= BYTES_PER_BLE_PCKT) {
                pCharacteristic->setValue(data + i, size - i);
                pCharacteristic->indicate();
                return;
            }
            pCharacteristic->setValue(data + i, BYTES_PER_BLE_PCKT);
            pCharacteristic->indicate();
        }
    }
    else {
        pCharacteristic->setValue(data, size);
        pCharacteristic->indicate();
    }
}

void updateThreshold_wrapper() {
    hall_signal.update_trshld();
}