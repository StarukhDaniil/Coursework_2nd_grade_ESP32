#pragma once

#include "hall_signal.h"
#include <LiquidCrystal_I2C.h>
#include <HardwareSerial.h>


extern HallSignal hall_signal;
extern HardwareSerial uart(2);
extern LiquidCrystal_I2C lcd(0x27, 20, 4);
extern hw_timer_t* Timer0_Cfg = nullptr;

extern uint16_t ADC_value = 0;
extern uint16_t counter = 0;

extern uint8_t a = 0;