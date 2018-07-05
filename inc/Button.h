#ifndef _BUTTON_H
#define _BUTTON_H

typedef enum{
  BUTTON_RELEASE,
  BUTTON_PRESSED,
}ButtonState;

/*
return non-zero if button is press, otherwise zero.
*/
ButtonState getButtonState(void);
#endif // _BUTTON_H
