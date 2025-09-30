#pragma once

#include <Arduino.h>

#define UART2_BAUD 115200
#define UART2_RX 16
#define UART2_TX 17
#define RQST_FOR_DATA 0x01

void IRAM_ATTR Timer0_ISR();
void setup_uart2();
void setup_lcd();
void setup_timer0();