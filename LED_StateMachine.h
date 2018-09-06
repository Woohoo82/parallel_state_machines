//LED State Machine variables

#ifndef __LED_SM__
#define __LED_SM__

enum LED_state {led_RESET,
                led_WAIT,
                led_TURN_ON,
                led_ON,
                led_TURN_OFF,
                led_OFF };

typedef struct {
  enum LED_state state;     //The actual state of the state machine
  enum LED_state state_prev;//Remember the previous state (useful to know if the state has changed)
  uint8_t  pin;         //Buzzer pin
  uint8_t  val;         //Buzzer value (on or off)
  uint32_t t;           //Current time of the buzzer state machine (in milli seconds)
  uint32_t t_0;         //The time that we last passed through a state of interest (in milli seconds)
  uint16_t on_delay;    //On time for the buzzer as it beeps (in milli seconds)
  uint16_t off_delay;   //Off time for the buzzer as it beeps (in milli seconds)
  uint8_t  beep_count;  //Number of times we've beeped on this journey
  uint8_t  beep_number; //Number of times we should beep before resetting
} LED_StateMachine;

#endif
