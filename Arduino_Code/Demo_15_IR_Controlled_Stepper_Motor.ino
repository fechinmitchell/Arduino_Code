#include "Stepper.h"
#include "IRremote.h"
 
/*----- Variables, Pins -----*/
#define STEPS  32   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // 2048 = 1 Revolution
int receiver = 1; // Signal Pin of IR receiver to Arduino Digital Pin 6
#define code1 0xFF02FD
#define code2 0xFF22DD
 
/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4
 
Stepper small_stepper(STEPS, 2, 3, 4, 5);
Stepper small_stepper1(STEPS, 5, 4, 3, 2);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'
 
void setup()
{ 
  irrecv.enableIRIn(); // Start the receiver
}
 
void loop()
{
if (irrecv.decode(&results)) // have we received an IR signal?
 
  {
    switch(results.value)
 
    {
 
      case code1: // UP button pressed
                      small_stepper.setSpeed(700); //Max seems to be 700
                      Steps2Take  =  2048;  // Rotate CW
                      small_stepper.step(Steps2Take);
                      delay(2000); 
                      break;
  
      case code2: // DOWN button pressed
                      small_stepper1.setSpeed(700);
                      Steps2Take  =  -2048;  // Rotate CCW
                      small_stepper1.step(Steps2Take);
                      delay(2000); 
                      break;
                      
    }
    
      irrecv.resume(); // receive the next value
  }  
 
 
}/* --end main loop -- */
