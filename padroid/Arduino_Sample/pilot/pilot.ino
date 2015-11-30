#include "padroid.h"

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
  pd_setup();
  
  pd_set_callback(_on_leftpad, _on_rightpad, _on_select_button, _on_start_button);
}

void loop() {
  pd_receive();
}
