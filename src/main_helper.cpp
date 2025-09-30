#include "main_helper.h"
#include "hall_signal.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "main_instances.h"

void IRAM_ATTR Timer0_ISR() {
  hall_signal.update_trshld();
  if (hall_signal.info() & SIGNAL_VALUE) {
    digitalWrite(23, HIGH);
  }
  else {
    digitalWrite(23, LOW);
  }
}

void setup_uart2() {
  uart.begin(UART2_BAUD, SERIAL_8N1, UART2_RX, UART2_TX);
  uart.setRxBufferSize(2);
  uart.write(RQST_FOR_DATA);
}

void setup_lcd() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 3);
}

void setup_timer0() {
  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 1000000, true);
  timerAlarmEnable(Timer0_Cfg);
}