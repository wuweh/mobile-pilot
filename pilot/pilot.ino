#include "padroid.h"
#include <Wire.h>   
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

static void _on_leftpad(int x, int y) {
  Serial.print("L: ");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print('\n');
}

static void _on_rightpad(int x, int y) {
  Serial.print("R: ");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print('\n');
}

static void _on_select_button(int s) {
  if (s == 1)
    Serial.println("Select down");
  else if (s == -1)
    Serial.println("Select up");
}

static void _on_start_button(int s) {
  if (s == 1)
    Serial.println("Start down");
  else if (s == -1)
    Serial.println("Start up");
}

void setup() {
  lcd.init();                      // initialize the lcd 
 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Hello, world!");
  lcd.setCursor(3,1);
  lcd.print("IEG_TEST");
  
  pd_setup();
  
  pd_set_callback(_on_leftpad, _on_rightpad, _on_select_button, _on_start_button);
}

void loop() {
  pd_receive();
}

