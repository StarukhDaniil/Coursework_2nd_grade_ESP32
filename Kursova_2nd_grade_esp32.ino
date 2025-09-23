// #include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
HardwareSerial uart(2);

#define UART2_BAUD 115200
#define UART2_RX 16
#define UART2_TX 17

uint16_t uart_value = 0;

void setup() {
  uart.begin(UART2_BAUD, SERIAL_8N1, UART2_RX, UART2_TX);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("");
}

void loop() {
  if (uart.available()) {
    uart.readBytes((uint8_t*)(&uart_value), 2);
    lcd.setCursor(0, 0);
    lcd.print(String(uart_value) + "    ");
  }
}