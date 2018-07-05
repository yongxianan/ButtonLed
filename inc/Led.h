#ifndef _LED_H
#define _LED_H

typedef enum{
    LED_ON,
    LED_OFF,
}LedState;

void turnLed(LedState state);
#endif // _LED_H
