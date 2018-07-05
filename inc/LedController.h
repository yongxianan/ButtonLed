#ifndef _LEDCONTROLLER_H
#define _LEDCONTROLLER_H

#include "Led.h"
#include "Button.h"
typedef struct LedButtonInfo LedButtonInfo;
struct LedButtonInfo{
  LedState previousLedState;
  ButtonState previousButtonState;
};
void doTapTurnOnTapTurnOffLed(LedButtonInfo *info);
//void turnOnLedIfButtonIsPressed(void);

#endif // _LEDCONTROLLER_H
