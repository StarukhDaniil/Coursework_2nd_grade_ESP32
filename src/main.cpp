#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <esp32-hal-timer.h>
#include <HardwareSerial.h>
#include "signal_processing.h"
#include "main_helper.h"

HallSignal hall_signal;

HardwareSerial uart(2);
LiquidCrystal_I2C lcd(0x27, 20, 4);
hw_timer_t* Timer0_Cfg = nullptr;

#define UART2_BAUD 115200
#define UART2_RX 16
#define UART2_TX 17

uint16_t ADC_value = 0;
uint16_t counter = 0;

uint8_t a = 0;

void setup() {
  uart.begin(UART2_BAUD, SERIAL_8N1, UART2_RX, UART2_TX);
  uart.setRxBufferSize(2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 3);

  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 1000000, true);
}

void loop() {
  if (uart.available() > 0) {
    uart.readBytes((uint8_t*)(&ADC_value), sizeof(ADC_value));
    ++counter;

    a = ADC_value >> 8;
    a |= ((ADC_value & 0x00ff) << 8);

    lcd.setCursor(0, 0);
    lcd.print(String(ADC_value) + "    ");
    lcd.setCursor(10, 0);
    lcd.print(String(a) + "    ");
    lcd.setCursor(0, 1);
    lcd.print(String(counter) + "    ");
    while(uart.available()) {
      uart.read();
    }
  }
}