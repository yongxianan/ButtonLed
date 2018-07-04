#include "LedController.h"
/*
void turnOnLedIfButtonIsPressed(LedButtonInfo *info){
  while(info->currentLedState==LED_OFF && info->previousButtonState==BUTTON_RELEASE){
    }
}
*/
void doTapTurnOnTapTurnOffLed(LedButtonInfo *info){
  ButtonState current=getButtonState();
  if((info->previousLedState==LED_OFF)){
    if((info->previousButtonState == BUTTON_RELEASE) && (current==BUTTON_PRESSED)){
      turnLed(LED_ON);
      info->previousButtonState = current;
    }
    else if((info->previousButtonState == BUTTON_PRESSED) && (current==BUTTON_RELEASE)){
      info->previousLedState=LED_ON;
      info->previousButtonState = current;
    }
    else{
      info->previousButtonState = current;
    }
  }
  else if((info->previousLedState==LED_ON) && (info->previousButtonState == BUTTON_PRESSED) && (current==BUTTON_RELEASE)){
    turnLed(LED_OFF);
    info->previousLedState=LED_OFF;
    info->previousButtonState = current;
  }
  else{
      info->previousButtonState = current;
  }
}
/*
void doTurnOnLedOnButtonPressedAndHoldController(){
  while(1){
    turnOnLedIfButtonIsPressed();
  }
}

void doTapTapLedController(){
  while(1){
    //tapTurnOnTapTurnOffLed(&currentLedState;);
  }
}
*/
