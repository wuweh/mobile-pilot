#include "padroid.h"

#define _TAKE1(p0) (_buf[0] == (p0))
#define _TAKE2(p0, p1) ((_cursor == 2) && (_buf[0] == (p0)) && (_buf[1] == (p1)))

static pd_callback2 _leftpad = NULL;
static pd_callback2 _rightpad = NULL;
static pd_callback1 _select = NULL;
static pd_callback1 _start = NULL;

static char _buf[16];
static int _cursor = 0;

static void _pd_parse_vec2(int* x, int* y) {
  char* part = strtok(_buf + 1, ",");
  *x = atoi(part);
  part = strtok(0, ",");
  *y = atoi(part);
}

static void _pd_parse(void) {
  _cursor--;

  if (_TAKE2('l', 'u')) {
    if (_leftpad) _leftpad(0, 0);
  } else if (_TAKE2('r', 'u')) {
    if (_rightpad) _rightpad(0, 0);
  } else if (_TAKE2('s', 'd')) {
    if (_select) _select(1);
  } else if (_TAKE2('s', 'u')) {
    if (_select) _select(-1);
  } else if (_TAKE2('t', 'd')) {
    if (_start) _start(1);
  } else if (_TAKE2('t', 'u')) {
    if (_start) _start(-1);
  } else if (_TAKE1('<')) {
    int x, y;
    _pd_parse_vec2(&x, &y);
    if (_leftpad) _leftpad(x, y);
  } else if (_TAKE1('>')) {
    int x, y;
    _pd_parse_vec2(&x, &y);
    if (_rightpad) _rightpad(x, y);
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

void pd_receive(void) {
  while (Serial.available()) {
    int r = Serial.read();
    //Serial.write(r);
    _buf[_cursor++] = (char)r;
    if (r == ';') {
      _pd_parse();

      _cursor = 0;
    }
  }
}

