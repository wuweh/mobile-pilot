#ifndef __BLUNO_H__
#define __BLUNO_H__

extern "C" {

void bl_open(void);

void bl_close(void);

void bl_connect(void);

void bl_send(const char* msg);

void bl_msg_box(const char* title, const char* message);

}

#endif // __BLUNO_H__
