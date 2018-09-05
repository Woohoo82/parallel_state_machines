#include "LED_StateMachine.h"

void LED_StateMachine_do(LED_StateMachine &l) {

  //Almost every state needs these lines so I'll put it outside the State Machine
  l.state_prev = l.state;

  //State Machine Section
  switch(l.state) {
    case led_RESET:
      //Set Beep Count to 0 then proceed to WAIT
      l.beep_count = 0;
      l.state = led_WAIT;
    break;

    case led_WAIT:
      //do nothing, the main loop can progress this Machine from state 1 to state 2
    break;

    case led_TURN_ON:
      //Start buzzer, record time then proceed to ON, 
      digitalWrite(l.pin,HIGH);
      l.t_0 = millis();
      l.state = led_ON;
    break;

    case led_ON:
      //Wait for time to elapse, then proceed to TURN OFF
      l.t = millis();
      if (l.t - l.t_0 > l.on_delay) {l.state = led_TURN_OFF;}
    break;

    case led_TURN_OFF:
      //Increment the beep counter, turn off buzzer, proceed to OFF
      l.beep_count++;
      l.t_0 = millis();
      digitalWrite(l.pin,LOW);
      l.state = led_OFF;
    break;

    case led_OFF:
      l.t = millis();
      if (l.t - l.t_0 > l.off_delay) {l.state = led_TURN_ON;}
      if (l.beep_count >= l.beep_number) {l.state = led_RESET;}
    break;
  }
}
