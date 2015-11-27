#ifndef __PADROID_H__
#define __PADROID_H__

/**
 * @brief Value range: 1 or -1.
 */
typedef void (* pd_callback1)(int);

/**
 * @brief Value range: -255 to 255.
 */
typedef void (* pd_callback2)(int, int);

/**
 * @brief Initializes padroid.
 */
void pd_setup(void);

/**
 * @brief Sets event callbacks.
 * @note The first parameter of pd_callback2 means data of X-Axis, the second means Y-Axis;
 *       The parameter of pd_callback1 means pressed down if the value is 1, up if -1.
 *
 * @param leftpad - Callback of left side D-Pad.
 * @param rightpad - Callback of right side D-Pad.
 * @param select - Callback of select button.
 * @param start - Callback of start button.
 */
void pd_set_callback(pd_callback2 leftpad, pd_callback2 rightpad, pd_callback1 select, pd_callback1 start);

/**
 * @brief You need to call this function each frame.
 */
void pd_receive(void);

#endif // __PADROID_H__
