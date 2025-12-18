#pragma once

#include <Arduino.h>

#define SPI2_BAUD 20000000
#define SPI2_MOSI 17
#define SPI2_MISO 16
#define SPI2_CLK 18
#define SPI2_SS 5

#define RX_DATA_BUFF_SIZE 64
// how many results are in one SPI transaction
#define RSLTS_PER_PCKT RX_DATA_BUFF_SIZE / 2

void setup_spi2();
void updateThreshold_wrapper();
void sendData(uint8_t* data, size_t size);