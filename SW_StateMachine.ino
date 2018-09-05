#include "SW_StateMachine.h"

void SW_StateMachine_do(SW_StateMachine &s) {
  
  //Almost every state needs these lines, so I'll put it outside the State Machine
  s.val = digitalRead(s.pin);
  s.state_prev = s.state;

  //State Machine Section
  switch (s.state) {
    case sw_RESET:
      //Catch all "home base" for the State MAchine
      s.state = sw_WAIT;
    break;

    case sw_WAIT:
      //Wait for the switch to go low
      if (s.val == LOW) {s.state = sw_ARMING;}
    break;

    case sw_ARMING:
      //Record the time and proceed to ARMED
      s.t_0 = millis();
      s.state = sw_ARMED;
    break;

    case sw_ARMED:
      //Check to see if the proper has delay has passed.  If a bounce occures then RESET
      s.t = millis();
      if (s.t - s.t_0 > s.bounce_delay) {s.state = sw_DRAWN;}
      if (s.val == HIGH) {s.state = sw_RESET;}
    break;

    case sw_DRAWN:
      //If switch goes HIGH, then TRIGGER. Also check timer for a "Long Pess"
      s.t = millis();
      if (s.val == HIGH) {s.state = sw_TRIGGERED;}
      if (s.t - s.t_0 > s.hold_delay) {s.state = sw_HOLD;}
    break;

    case sw_TRIGGERED:
      //reset the State Machine
      if (DEBUG) {Serial.println("TRIGGERED!!");}
      s.state = sw_RESET;
    break;

    case sw_HOLD:
      //proceed to LOW WAIT
      if (DEBUG) {Serial.println("HOLDED!!");}
      s.state = sw_LOW_WAIT;
    break;

    case sw_LOW_WAIT:
      //wait for switch to go back HIGH, then reset
      if (s.val == HIGH) {s.state = sw_RESET;}
    break;
  } 
}
