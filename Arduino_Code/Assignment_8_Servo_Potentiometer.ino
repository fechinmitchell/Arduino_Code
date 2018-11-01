#include <Servo.h>

Servo myservo; // reate servo object to control a servo

int potPin = 0; // analog pin used to connect the potientiometer
int val; //variable to read the value from the analog pin

void setup(){
  myservo.attach(9); // attaches the servo on pin 9 to the servo object
}

void loop(){
  val = analogRead(potPin); //reads the value of the potentiometer
  val = map(val, 0, 1023, 0, 180); // scale it to use it with the servo value between 0 to 180
  myservo.write(val); // sets the servo position according to the scaled value
  delay(15); // waits for the servo to get there
  }

