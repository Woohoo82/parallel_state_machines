//Switch Variables

#ifndef __SW_SM__
#define __SW_SM__

enum SW_state {sw_RESET,
               sw_WAIT,
               sw_ARMING,
               sw_ARMED,
               sw_DRAWN,
               sw_TRIGGERED,
               sw_HOLD,
               sw_LOW_WAIT };

typedef struct {
  enum SW_state state;       //The actual ~state~ of the state machine
  enum SW_state state_prev;  //Remembers the previous state (useful to know when the state has changed)
  unsigned char pin;         //Input/Output (IO) pin for the switch
  unsigned char val;         //Value of the switch ("HIGH" or "LOW")
  unsigned long t;           //Typically represents the current time of the switch
  unsigned long t_0;         //The time that we last passed through an interesting state
  unsigned int bounce_delay; //The delay to list for bouncing
  unsigned int hold_delay;   //The time required to register a long press (a.k.a. "hold")
} SW_StateMachine;

#endif
