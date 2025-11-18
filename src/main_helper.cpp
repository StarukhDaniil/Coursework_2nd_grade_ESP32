#include "main_helper.h"
#include "hall_signal.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "main_instances.h"

static uint8_t cmd;

void IRAM_ATTR Timer0_ISR() {
    // hall_signal.update_trshld();
}

void setup_spi2() {
    spi2Slave.begin(VSPI, SPI2_CLK, SPI2_MISO, SPI2_MOSI, SPI2_SS);
    spi2Slave.setDataMode(SPI_MODE0);
}

void setup_lcd() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
}

void setup_timer0() {
    Timer0_Cfg = timerBegin(0, 80, true);
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
    timerAlarmWrite(Timer0_Cfg, 1000000, true);
    timerAlarmEnable(Timer0_Cfg);
}