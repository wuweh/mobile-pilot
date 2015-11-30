#include "bluno.h"
#include "bluno_impl.h"

static BlunoImpl* impl = NULL;

extern "C" {

void bl_open(void) {
	impl = [[BlunoImpl alloc] init];
    [impl open];
}

void bl_close(void) {
    [impl close];
	//[impl release];
	impl = NULL;
}

void bl_connect(void) {
	[impl connect];
}

void bl_send(const char* msg) {
	[impl send: [NSString stringWithUTF8String: msg]];
}

void bl_msg_box(const char* title, const char* message) {
    UIAlertView* alert = [[UIAlertView alloc] initWithTitle: [NSString stringWithUTF8String: title]
                                                    message: [NSString stringWithUTF8String: message]
                                                    delegate: nil
                                            cancelButtonTitle: @"OK"
                                            otherButtonTitles: nil
                            ];
    [alert show];
    //[alert release];
}

}
