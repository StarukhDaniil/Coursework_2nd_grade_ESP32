#pragma once

#include "hall_signal.h"
#include <LiquidCrystal_I2C.h>
#include <ESP32SPISlave.h>


extern HallSignal hall_signal;
extern ESP32SPISlave spi2Slave;
extern LiquidCrystal_I2C lcd;
extern hw_timer_t* Timer0_Cfg;

extern uint16_t ADC_value;
extern uint16_t counter;