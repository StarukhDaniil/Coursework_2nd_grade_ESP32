#pragma once
#include <BLECharacteristic.h>

#include "hall_signal.h"
#include <ESP32SPISlave.h>

#ifndef RX_DATA_BUFF_SIZE
#define RX_DATA_BUFF_SIZE 64
#endif

#ifndef RSLTS_PER_PCKT
// how many results are in one SPI transaction
#define RSLTS_PER_PCKT RX_DATA_BUFF_SIZE / 2
#endif


extern HallSignal hall_signal;
extern ESP32SPISlave spi2Slave;

extern BLECharacteristic *pCharacteristic;
extern bool deviceConnected;