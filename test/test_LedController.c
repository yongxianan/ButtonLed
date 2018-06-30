#include "unity.h"
#include "LedController.h"
#include "mock_Button.h"
#include "mock_Led.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_doTapTurnOnTapTurnOffLed_given_led_is_off_and_button_is_pressed_and_released_expect_led_to_turn_on(void){
  LedButtonInfo info={LED_OFF,BUTTON_RELEASE};

  getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_ON);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  doTapTurnOnTapTurnOffLed(&info);

  TEST_ASSERT_EQUAL(LED_ON,info.previousLedState);
}

void test_doTapTurnOnTapTurnOffLed_given_led_is_on_and_button_is_pressed_and_released_expect_led_to_turn_off(void){
  LedButtonInfo info={LED_ON,BUTTON_RELEASE};

  getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  turnLed_Expect(LED_OFF);
  doTapTurnOnTapTurnOffLed(&info);

  TEST_ASSERT_EQUAL(LED_OFF,info.previousLedState);
}
/*
void test_turnOnLedIfButtonIsPressed_given_button_is_pressed_expect_led_is_turned_on(void){
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_ON);
  turnOnLedIfButtonIsPressed();
}

void test_turnOnLedIfButtonIsPressed_given_button_is_pressed_and_released_expect_led_is_turned_off(void){
  getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  turnLed_Expect(LED_OFF);
  turnOnLedIfButtonIsPressed();
}*/
  //getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  //turnLed_Expect(LED_ON);
  //turnOnLedIfButtonIsPressed();
  //button=getButtonState();
  //TEST_ASSERT_EQUAL(30,button);
  //printf("button: %d\n",button);
  //button=getButtonState();
  //TEST_ASSERT_EQUAL(30,button);
  //printf("button: %d\n",button);

/*
void test_doTapTurnOnTapTurnOffLed_given_led_is_on_and_button_is_pressed_and_released_expect_led_to_turned_off(void){
  LedState currentLedState;
  //getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  //turnLed_Expect(LED_OFF);
  //turnOnLedIfButtonIsPressed();
  currentLedState=LED_ON;
  doTapTurnOnTapTurnOffLed(&currentLedState);
  TEST_ASSERT_EQUAL(LED_OFF,currentLedState);
}

void test_turnOnLedIfButtonIsPressed_given_button_is_pressed_expect_led_is_turned_on(void){
  int button;
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_ON);
  turnOnLedIfButtonIsPressed();
  //button=getButtonState();
  //TEST_ASSERT_EQUAL(30,button);
  //printf("button: %d\n",button);
  //button=getButtonState();
  //TEST_ASSERT_EQUAL(30,button);
  //printf("button: %d\n",button);
}

void test_LedController_given_button_is_pressed_expect_led_is_turned_off(void){
  getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  turnLed_Expect(LED_OFF);
  turnOnLedIfButtonIsPressed();
}
*/
