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

void IRAM_ATTR Timer0_ISR();
void setup_spi2();
void setup_lcd();
void setup_timer0();
bool ask_for_data();