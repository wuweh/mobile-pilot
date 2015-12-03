#include "padroid.h"
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

static const int pin1_x = 3;
static const int pin1_y = 9;
static const int pin2_x = 10;
static const int pin2_y = 11;
static int pin_val1_x = 128;
static int pin_val1_y = 128;
static int pin_val2_x = 128;
static int pin_val2_y = 128;
// 1 down, -1 up
static int funx_key1 = -1;
static int funx_key2 = -1;
//
static int funx_cycs = 0;



Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

static void _on_leftpad(int x, int y) {
  pin_val1_x = (x + 256) / 2;
  pin_val1_y = (y + 256) / 2;
  //Serial.print("L: ");
  //Serial.print(x);
  //Serial.print(",");
  //Serial.print(y);
  //Serial.print('\n');
}

static void _on_rightpad(int x, int y) {
  pin_val2_x = (x + 256) / 2;
  pin_val2_y = (y + 256) / 2;
  //Serial.print("R: ");
  //Serial.print(x);
  //Serial.print(",");
  //Serial.print(y);
  //Serial.print('\n');
}


static void _on_select_button(int s) {
  if (s == 1)
  {
    if (funx_cycs == 0)
    {
      funx_key1 = 1;
      // Serial.println("Select down");
    }
  }
  else if (s == -1)
  {
    if (funx_key1 == 1)
    {
      // Serial.println("Select up");
      funx_cycs = 50;
    }
  }
}

static void _on_start_button(int s) {
  if (s == 1)
  {
    if (funx_cycs == 0)
    {
      funx_key2 = 1;
      // Serial.println("Start down");
    }
  }
  else if (s == -1)
  {
    if (funx_key2 == 1)
    {
      // Serial.println("Start up");
      funx_cycs = 50;
    }
  }
}

void set_select()
{
  pin_val1_x = 0;
  pin_val2_x = 0;

  pin_val1_y = 255;
  pin_val1_y = 0;
}

void set_start()
{
  pin_val1_x = 0;
  pin_val2_x = 0;

  pin_val1_y = 0;
  pin_val1_y = 255;
}

void set_pin()
{
  // Serial.print(pin_val1_x);
  //Serial.print(",");
  //Serial.print(pin_val1_y);
  //Serial.print(",");
  //Serial.print(pin_val2_x);
  //Serial.print(",");
  //Serial.println(pin_val2_y);

  int pos1 = map(pin_val1_x, 0, 255, 0, 180);
  int pos2 = map(pin_val1_y, 0, 255, 0, 180);
  int pos3 = map(pin_val2_x, 0, 255, 0, 180);
  int pos4 = map(pin_val2_y, 0, 255, 0, 180);

  Serial.print(pos1);
  Serial.print(",");
  Serial.print(pos2);
  Serial.print(",");
  Serial.print(pos3);
  Serial.print(",");
  Serial.println(pos4);

  myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);

  //analogWrite(pin1_x, pin_val1_x);
  //analogWrite(pin1_y, pin_val1_y);
  //analogWrite(pin2_x, pin_val2_x);
  //analogWrite(pin2_y, pin_val2_y);

  if (funx_cycs > 0)
  {
    delay(50 * funx_cycs);
  }
  else
  {
    delay(50);
  }
}

void set_output()
{
  // func is first
  if (funx_cycs > 0)
  {
    if (funx_key1 == 1)
    {
      set_select();
    }
    else if (funx_key2 == 1)
    {
      set_start();
    }
    else
    {
      Serial.println("error swich func!");
    }
    set_pin();

    funx_cycs = 0;
    funx_key1 = 0;
    funx_key2 = 0;

    //pin_val1_x = 128;
    //pin_val1_y = 128;
    //pin_val2_x = 128;
    //pin_val2_y = 128;
  }
  else
  {
    set_pin();
  }
}

void setup() {
  //pinMode(pin1_x,OUTPUT);
  //pinMode(pin1_y,OUTPUT);
  //pinMode(pin2_x,OUTPUT);
  //pinMode(pin2_y,OUTPUT);

  myservo1.attach(pin1_x);
  myservo2.attach(pin1_y);
  myservo3.attach(pin2_x);
  myservo4.attach(pin2_y);


  lcd.init();                      // initialize the lcd

  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Hello, world!");
  lcd.setCursor(3, 1);
  lcd.print("IEG_TEST");

  pd_setup();

  pd_set_callback(_on_leftpad, _on_rightpad, _on_select_button, _on_start_button);

  pd_set_one_axis_mode_on_left(true);
  pd_set_one_axis_mode_on_right(true);
}

void loop() {
  pd_receive();
  set_output();
}

