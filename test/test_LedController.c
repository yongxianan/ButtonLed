#include "unity.h"
#include "LedController.h"
#include "mock_Button.h"
#include "mock_Led.h"

int turnLedCallNumbers=0;
int expectedGetButtonStateMaxCalls=0;
int expectedTurnLedMaxCalls=0;
ButtonState *expectedButtonStates=NULL;
LedState *expectedLedStates=NULL;

ButtonState *buttonstate;
void setUp(void)
{
}

void tearDown(void)
{
}
//my fake code
void fake_turnLed(LedState state,int NumCalls){
  turnLedCallNumbers++;
  if(NumCalls<expectedTurnLedMaxCalls){
    if(state!=expectedLedStates[NumCalls])
      TEST_FAIL_MESSAGE("turnLed() was called with ??, but expect ??");
  }
  else
    TEST_FAIL_MESSAGE("received extra getButtonState() calls");
}

ButtonState fake_getButtonState(int NumCalls){
  if(NumCalls < expectedGetButtonStateMaxCalls){
    return expectedButtonStates[NumCalls];
  }else
    TEST_FAIL_MESSAGE("received extra getButtonState() calls");
}

void setupFake(ButtonState buttStates, LedState expLedStates[],int ledMaxCalls,ButtonState buttStates[],int buttonMaxCalls){
  turnLedCallNumbers=0;
  turnLed_StubWithCallback(fake_turnLed);
  expectedButtonStates=expLedStates;
  expectedGetButtonStateMaxCalls=ledMaxCalls;
  getButtonState_StubWithCallback(fake_getButtonState);
  expectedButtonStates=buttStates;
  expectedGetButtonStateMaxCalls=buttonMaxCalls;
}
  
  
 
ButtonState fake_getButtonStateReleasePressedRelease(int NumCalls){
  switch(NumCalls){
    case 0:
    return BUTTON_RELEASE;
    case 1:
    return BUTTON_PRESSED;
    case 2:
    return BUTTON_RELEASE;
    default:
    TEST_FAIL_MESSAGE("received extra getButtonState() calls");
  }
}

void verfyTurnLedCalls(int numCalls){
  if(turnLedCallNumbers!=numCalls)
    TEST_FAIL_MESSAGE("turnLed() was not call at all.");
}




void test_doTapTurnOnTapTurnOffLed_given_led_is_off_and_button_is_pressed_and_released_expect_led_to_turn_on(void){
  LedButtonInfo info={LED_OFF,BUTTON_RELEASE};
  LedState expectedLedState[]={LED_ON};
  ButtonState buttonState[]={BUTTON_RELEASE,BUTTON_PRESSED,BUTTON_RELEASE};
  
  setupFake(expectedLedStates,1,expectedButtonStates,3);
  

  doTapTurnOnTapTurnOffLed(&info);
  doTapTurnOnTapTurnOffLed(&info);
  doTapTurnOnTapTurnOffLed(&info);
  
  verfyTurnLedCalls(1);

  TEST_ASSERT_EQUAL(LED_ON,info.previousLedState);
}

void test_doTapTurnOnTapTurnOffLed_given_led_is_on_and_button_is_pressed_and_released_expect_led_to_turn_off(void){
  LedButtonInfo info={LED_ON,BUTTON_RELEASE};
  ButtonState buttonState[]=(BUTTON_RELEASE,BUTTON_PRESSED,BUTTON_RELEASE);
  
  //turnLedCallNumbers=0;
  setupFake(buttonStates,3);
  turnLed_StubWithCallback(fake_turnLedOff);
  //getButtonState_StubWithCallback(fake_getButtonStateReleasePressedRelease);
  
  doTapTurnOnTapTurnOffLed(&info);
  doTapTurnOnTapTurnOffLed(&info);
  turnLed_Expect(LED_OFF);
  doTapTurnOnTapTurnOffLed(&info);

  verfyTurnLedCalls(1);
  
  TEST_ASSERT_EQUAL(LED_OFF,info.previousLedState);
}


/*
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

void test_doTapTurnOnTapTurnOffLed_MixedFirstTwoTestTogether(void){
  LedButtonInfo info={LED_ON,BUTTON_RELEASE};
  
  getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  turnLed_Expect(LED_OFF);
  doTapTurnOnTapTurnOffLed(&info);
  
  getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_PRESSED);
  turnLed_Expect(LED_ON);
  doTapTurnOnTapTurnOffLed(&info);
  getButtonState_ExpectAndReturn(BUTTON_RELEASE);
  doTapTurnOnTapTurnOffLed(&info);

  TEST_ASSERT_EQUAL(LED_ON,info.previousLedState);
}

void test_dotapTurnOntapTurnOffLed_given_led_is_on_and_is_relese__random_test_to_turned_on(void)
{
	LedButtonInfo info = {LED_ON, BUTTON_RELEASE}; //initial BUTTON_PRESSED & LED_ON cant do.
	
	
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);	
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_PRESSED);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	turnLed_Expect(LED_OFF);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_PRESSED);
	turnLed_Expect(LED_ON);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	
	TEST_ASSERT_EQUAL(LED_ON,info.previousLedState);
}

void test_dotapTurnOntapTurnOffLed_given_led_is_on_and_is_relese__random_test_to_turned_off(void)
{
	LedButtonInfo info = {LED_ON, BUTTON_RELEASE}; //initial BUTTON_PRESSED & LED_ON cant do.
	
	
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);	
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_PRESSED);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	turnLed_Expect(LED_OFF);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_PRESSED);
	turnLed_Expect(LED_ON);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_PRESSED);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_PRESSED);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_PRESSED);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_PRESSED);
	doTapTurnOnTapTurnOffLed(&info);
	getButtonState_ExpectAndReturn(BUTTON_RELEASE);
	turnLed_Expect(LED_OFF);
	doTapTurnOnTapTurnOffLed(&info);
	
	TEST_ASSERT_EQUAL(LED_OFF, info.previousLedState);
}*/

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
