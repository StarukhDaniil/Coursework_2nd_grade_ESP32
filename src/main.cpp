#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <esp32-hal-timer.h>
#include <ESP32SPISlave.h>
#include <Ticker.h>
#include "hall_signal.h"
#include "main_helper.h"

HallSignal hall_signal;
ESP32SPISlave spi2Slave;
hw_timer_t* Timer0_Cfg = nullptr;

Ticker logging_ticker;

uint8_t SPI2_RxBuff[RX_DATA_BUFF_SIZE] = {0};

int transactions_count = 0;
bool logging_allowed = false;

void on_logging_ticker() {
    logging_allowed = true;
}

void note_transaction_count() {
    Serial.printf("%i      \n", transactions_count);

    uint16_t* pRxBuff = reinterpret_cast<uint16_t*>(SPI2_RxBuff);

    for (size_t i = 0; i < 32; ++i) {
        Serial.printf("%i  ", *(pRxBuff + i));
    }

    Serial.printf("\n---------   %i\n", hall_signal.filter_value());

    transactions_count = 0;

    logging_allowed = false;
}

void setup() {
    pinMode(23, OUTPUT);
    setup_timer0();
    setup_spi2();

    logging_ticker.attach(1.0, on_logging_ticker);

    Serial.begin(115200);
}

void loop() {
    if (spi2Slave.remained() == 0 && spi2Slave.available() == 0) {
        spi2Slave.queue(SPI2_RxBuff, NULL, RX_DATA_BUFF_SIZE);
    }

    if (spi2Slave.available()) {
        ++transactions_count;
        // pointer for reading buffer as uint16_t
        uint16_t* pRxBuff = reinterpret_cast<uint16_t*>(SPI2_RxBuff);

        for (size_t i = 0; i < RSLTS_PER_PCKT; ++i) {
            hall_signal.add_value(*(pRxBuff + i));
        }

        spi2Slave.pop();
        
        if (logging_allowed) {
            note_transaction_count();
        }
    }
}