#include "padroid.h"

#define _TAKE1(p0) (_buf[0] == (p0))
#define _TAKE2(p0, p1) ((_cursor == 2) && (_buf[0] == (p0)) && (_buf[1] == (p1)))

static pd_callback2 _leftpad = NULL;
static pd_callback2 _rightpad = NULL;
static pd_callback1 _select = NULL;
static pd_callback1 _start = NULL;

static bool _left_down = false;
static bool _right_down = false;

static bool _one_axis_mode_on_left = false;
static bool _one_axis_mode_on_right = false;

static char _left_axis = 0;
static char _right_axis = 0;

static char _buf[16];
static int _cursor = 0;

static unsigned long _alive_timestamp = 0;

static void _pd_parse_vec2(int* x, int* y) {
  char* part = strtok(_buf + 1, ",");
  *x = atoi(part);
  part = strtok(0, ",");
  *y = atoi(part);
}

static void _pd_parse(void) {
  _cursor--;

  if (_TAKE2('l', 'd')) {
    _left_down = true;
  } else if (_TAKE2('r', 'd')) {
    _right_down = true;
  } else if (_TAKE2('l', 'u')) {
    if (_leftpad) _leftpad(0, 0);
    _left_axis = 0;
    _left_down = false;
  } else if (_TAKE2('r', 'u')) {
    if (_rightpad) _rightpad(0, 0);
    _right_axis = 0;
    _right_down = false;
  } else if (_TAKE2('s', 'd')) {
    if (_select) _select(1);
  } else if (_TAKE2('s', 'u')) {
    if (_select) _select(-1);
  } else if (_TAKE2('t', 'd')) {
    if (_start) _start(1);
  } else if (_TAKE2('t', 'u')) {
    if (_start) _start(-1);
  } else if (_TAKE1('<')) {
    if (_left_down) {
      int x, y;
      _pd_parse_vec2(&x, &y);
      if (_one_axis_mode_on_left) {
        int absx = abs(x), absy = abs(y);
        if (absx == 0 && absy == 0) _left_axis = 0;
        else if (!_left_axis) _left_axis = (absx > absy) ? 1 : -1;
        if (_left_axis == 1) y = 0;
        else if (_left_axis == -1) x = 0;
      }
      if (_leftpad) _leftpad(x, y);
    }
  } else if (_TAKE1('>')) {
    if (_right_down) {
      int x, y;
      _pd_parse_vec2(&x, &y);
      if (_one_axis_mode_on_right) {
        int absx = abs(x), absy = abs(y);
        if (absx == 0 && absy == 0) _right_axis = 0;
        else if (!_right_axis) _right_axis = (absx > absy) ? 1 : -1;
        if (_right_axis == 1) y = 0;
        else if (_right_axis == -1) x = 0;
      }
      if (_rightpad) _rightpad(x, y);
    }
  }
}

void pd_setup(void) {
  Serial.begin(115200);
  memset(_buf, 0, sizeof(_buf));
}

void pd_set_callback(pd_callback2 leftpad, pd_callback2 rightpad, pd_callback1 select, pd_callback1 start) {
  _leftpad = leftpad;
  _rightpad = rightpad;
  _select = select;
  _start = start;
}

void pd_set_one_axis_mode_on_left(bool enabled) {
  _one_axis_mode_on_left = enabled;
}

void pd_set_one_axis_mode_on_right(bool enabled) {
  _one_axis_mode_on_right = enabled;
}

void pd_receive(void) {
  unsigned long now = millis();
  if (Serial.available()) {
    _alive_timestamp = now;
  } else {
    if (now - _alive_timestamp > 1200) {
      _alive_timestamp = now;
      if (_leftpad) _leftpad(0, 0);
      if (_rightpad) _rightpad(0, 0);
    }
  }

  while (Serial.available()) {
    int r = Serial.read();
    _buf[_cursor++] = (char)r;
    if (r == ';') {
      _pd_parse();

      _cursor = 0;
    }
  }
}
