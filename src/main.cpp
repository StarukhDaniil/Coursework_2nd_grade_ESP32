#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <esp32-hal-timer.h>
#include <HardwareSerial.h>
#include "hall_signal.h"
#include "main_helper.h"

HallSignal hall_signal;
HardwareSerial uart(2);
LiquidCrystal_I2C lcd(0x27, 20, 4);
hw_timer_t* Timer0_Cfg = nullptr;

uint16_t ADC_value = 0;
uint16_t counter = 0;

uint8_t a = 0;

void setup() {
  pinMode(23, OUTPUT);
  setup_timer0();
  setup_lcd();
  setup_uart2();
}

void loop() {
  if (uart.available() > 0) {
    uart.readBytes((uint8_t*)(&ADC_value), sizeof(ADC_value));

    hall_signal.add_value(ADC_value);

    
    // ++counter;

    // a = ADC_value >> 8;
    // a |= ((ADC_value & 0x00ff) << 8);

    // lcd.setCursor(0, 0);
    // lcd.print(String(ADC_value) + "    ");
    // lcd.setCursor(10, 0);
    // lcd.print(String(a) + "    ");
    // lcd.setCursor(0, 1);
    // lcd.print(String(counter) + "    ");
    // while(uart.available()) {
    //   uart.read();
    // }
  }
}