//Description:
//  -A State Machine is a useful tool to organize complex code
//  -Think of it like the next step beyone "If Else" statements
//  -This example code uses a State Machine to handle tac switch debouncing
//  -It also has a "Hold" function to enable interaction with long button presses
//  -The tac switch is used to control a buzzer and an LED, it can multitask
//
//Wiring Instructions:
//  -Wire a SPST momentary switch between a Digital IO Pin 12 and Ground.  
//    (we will use an internal pullup resistor, so no need to worry about wiring a resistor)
//  -Wire an LED and a small resistor (~300 Ohm) in series
//  -Wire the series LED & Resistor between  Digital IO Pin 7 and Ground.
//    (be sure the + terminal of the LED points toward the IO pin)

#include "SW_StateMachine.h"
#include "LED_StateMachine.h"

// TODO enumerators for states

//Top Level Variables:
int DEBUG = 1;  //Set to 1 to enable serial monitor debugging info

SW_StateMachine  sw1;
LED_StateMachine bz1;
LED_StateMachine led1;

void setup() {
  // initialize digital pins
  pinMode(sw1.pin,INPUT_PULLUP); //INPUT_PULLUP will use the Arduino's internal pullup resistor
  pinMode(bz1.pin,OUTPUT);
  pinMode(led1.pin,OUTPUT);

  sw1.state      = sw_RESET;
  sw1.state_prev = sw_RESET;
  sw1.pin        = 12;
  sw1.val        = 0;
  sw1.t          = 0;
  sw1.t_0        = 0;
  sw1.bounce_delay = 10;
  sw1.hold_delay = 1000;
  
  bz1.state      = led_RESET;
  bz1.state_prev = led_RESET;
  bz1.pin        = 6;
  bz1.val        = 0;
  bz1.t          = 0;
  bz1.t_0        = 0;
  bz1.on_delay   = 500;
  bz1.off_delay  = 500;
  bz1.beep_count = 0;
  bz1.beep_number= 4;
  
  led1.state      = led_RESET;
  led1.state_prev = led_RESET;
  led1.pin        = 7;
  led1.val        = 0;
  led1.t          = 0;
  led1.t_0        = 0;
  led1.on_delay   = 500;
  led1.off_delay  = 500;
  led1.beep_count = 0;
  led1.beep_number= 4;

  //if DEBUG is turned on, intiialize serial connection
  if(DEBUG) {Serial.begin(115200);Serial.println("Debugging is ON");}
}

void loop() {
  //Instruct all the state machines to proceed one step (sometimes called a "cycle)
  SW_StateMachine( sw1 );
  LED_StateMachine_do( bz1 );
  LED_StateMachine_do( led1);

  //Provide events that can force the state machines to change state
  //I like to program interactions between state machines here in the top level loop
  if (sw1.state == 5) {led1.state = led_TURN_ON;} //short press
  if (sw1.state == 6) {bz1.state  = led_TURN_ON;} //long press

  if(DEBUG) {
    //Make a note whenever a state machine changes state
    //("Is the current state different from the previous? Yes? OK well let's tell the world the new state")
    if((sw1.state_prev != sw1.state) | (led1.state_prev != led1.state) | (bz1.state_prev != bz1.state)) {
      Serial.print("Switch State: "); Serial.print(sw1.state);
      Serial.print(" | LED State: "); Serial.print(led1.state);
      Serial.print(" | Buzzer State: "); Serial.println(bz1.state);
    }
  }
}
