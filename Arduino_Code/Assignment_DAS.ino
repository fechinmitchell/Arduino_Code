#include "Stepper.h"
#include "IRremote.h"
 
/*----- Variables, Pins -----*/
#define STEPS  32   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // 2048 = 1 Revolution
int receiver = 1; // Signal Pin of IR receiver to Arduino Digital Pin 6
int led8 = 8;
int itsONled[] = {0,0,0,0};
 
/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4
#define code1 0xFF02FD
#define code2 0xFF22DD
#define code3 0xFFC23D
#define code4 0xFF906F
Stepper small_stepper(STEPS, 2, 3, 4, 5);

IRrecv irrecv(receiver);    // create instance of 'irrecv'

decode_results results;     // create instance of 'decode_results'
 
void setup(){
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led8, OUTPUT);
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
                      small_stepper.setSpeed(700);
                      Steps2Take  =  2048;  // Rotate CCW
                      small_stepper.step(Steps2Take);
                      delay(2000); 
                      break;

      case code3: // Play/Pause button pressed
                        if(itsONled[8] == 1) {
                          digitalWrite(led8, LOW);
                          itsONled[8] = 0;
                        }
                          else {
                            digitalWrite(led8, HIGH);
                            itsONled[8] = 1;   
                      }
                       break;
                       
      case code4: // EQ button pressed
                        if(itsONled[8] == 1) {
                          digitalWrite(led8, HIGH);
                          itsONled[8] = 0;
                        }
                          else {
                            digitalWrite(led8, LOW);
                            itsONled[8] = 1;   
                      }
                       break;
    }
    
      irrecv.resume(); // receive the next value
  }  
 
 
}
