#include <Servo.h>
Servo myservo; // create servo object to control a servo
// twelve servo objects can be created on most boards
int pos = 0; // variable to store the servo angle
int button = 12; // one button is attached to pin 12
int button2 = 13; // other button is attached to pin 13

void setup() 
{
myservo.attach(9); // Servo is attached to pin 9
}

void loop()
{
if(digitalRead(button) == HIGH) // Here we check if the first button is pushed
{
if(pos <= 165) // Here we check if the servo has not completed 180* rotation. 
{
  myservo.write(pos+150); // Here we rotate the servo by 15* 
  delay(2000); // delay for rotation of servo 
    } 
  } 
if(digitalRead(button2) == HIGH) // here we check if the second button is pressed 
  { 
    if(pos >= 15); // Here we check if the Servo has not reached the 0* mark
  }
{
  myservo.write(pos-150); // here we rotate the servo by 15* in opposite direction
  delay(2000); //delay is for the servo to rotate;
    } 
  }
