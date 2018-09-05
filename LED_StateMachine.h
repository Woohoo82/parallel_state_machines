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
  unsigned char pin;        //Buzzer pin
  unsigned char val;        //Buzzer value (on or off)
  unsigned long t;          //Current time of the buzzer state machine (in milli seconds)
  unsigned long t_0;        //The time that we last passed through a state of interest (in milli seconds)
  unsigned int  on_delay;   //On time for the buzzer as it beeps (in milli seconds)
  unsigned int  off_delay;  //Off time for the buzzer as it beeps (in milli seconds)
  unsigned char beep_count; //Number of times we've beeped on this journey
  unsigned char beep_number;//Number of times we should beep before resetting
} LED_StateMachine;

#endif
