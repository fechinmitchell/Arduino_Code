#include <WProgram.h> //standard types and constants of the Arduino language

enum Num { NOTHING = -1, ZERO = 0, ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5,
SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9, DECIMAL_POINT = 10}; // 10 means decimal point, -1 means nothing is being displayed

class LEDDisplay {

public:
Num displaying; // indicate which number is being displayed

private:
int aPin; // these are the output pins
int bPin;
int cPin;
int dPin;
int ePin;
int fPin;
int gPin;
int dpPin;

int y1Pin; // these are used to control display which digit
int y2Pin;
int y3Pin;
int y4Pin;

public:
LEDDisplay(); // constructor with default output pins
LEDDisplay(int a, int b, int c, int d, int e, int f, int g, int dp, int y1, int y2, int y3, int y4); // constructor with specified output pins
void DisplayDigit (Num digit);
void DisplayNumber (int number);

};
[/sourcecode]

 

[sourcecode language=”cpp”]

#include "Seven_Seg_LED_Display.h"

LEDDisplay::LEDDisplay () {

displaying = NOTHING;

for (int outputPin = 1; outputPin <= 8; outputPin++)
pinMode(outputPin, OUTPUT);

// LED pin
aPin = 1;
bPin = 2;
cPin = 3;
dPin = 4;
ePin = 5;
fPin = 6;
gPin = 7;
dpPin = 8;

for (int yPin = 10; yPin <= 13; yPin++)
pinMode(yPin, OUTPUT);

// control to display which digit
y1Pin = 10;
y2Pin = 11;
y3Pin = 12;
y4Pin = 13;

}

LEDDisplay::LEDDisplay(int a, int b, int c, int d, int e, int f, int g, int dp, int y1, int y2, int y3, int y4) {

displaying = NOTHING;

pinMode(aPin = a, OUTPUT);
pinMode(bPin = b, OUTPUT);
pinMode(cPin = c, OUTPUT);
pinMode(dPin = d, OUTPUT);
pinMode(ePin = e, OUTPUT);
pinMode(fPin= f, OUTPUT);
pinMode(gPin = g, OUTPUT);
pinMode(dpPin = dp, OUTPUT);
pinMode(y1Pin = y1, OUTPUT);
pinMode(y2Pin = y2, OUTPUT);
pinMode(y3Pin = y3, OUTPUT);
pinMode(y4Pin = y4, OUTPUT);

}

void LEDDisplay::DisplayDigit (Num digit){

displaying = digit;

switch (digit) {
case ZERO:
digitalWrite(aPin, HIGH);
digitalWrite(bPin, HIGH);
digitalWrite(cPin, HIGH);
digitalWrite(dPin, HIGH);
digitalWrite(ePin, HIGH);
digitalWrite(fPin, HIGH);
digitalWrite(gPin, LOW);
digitalWrite(dpPin, LOW);
break;

case ONE:
digitalWrite(aPin, LOW);
digitalWrite(bPin, HIGH);
digitalWrite(cPin, HIGH);
digitalWrite(dPin, LOW);
digitalWrite(ePin, LOW);
digitalWrite(fPin, LOW);
digitalWrite(gPin, LOW);
digitalWrite(dpPin, LOW);
break;
case TWO:
digitalWrite(aPin, HIGH);
digitalWrite(bPin, HIGH);
digitalWrite(cPin, LOW);
digitalWrite(dPin, HIGH);
digitalWrite(ePin, HIGH);
digitalWrite(fPin, LOW);
digitalWrite(gPin, HIGH);
digitalWrite(dpPin, LOW);
break;
case THREE:
digitalWrite(aPin, HIGH);
digitalWrite(bPin, HIGH);
digitalWrite(cPin, HIGH);
digitalWrite(dPin, HIGH);
digitalWrite(ePin, LOW);
digitalWrite(fPin, LOW);
digitalWrite(gPin, HIGH);
digitalWrite(dpPin, LOW);
break;
case FOUR:
digitalWrite(aPin, LOW);
digitalWrite(bPin, HIGH);
digitalWrite(cPin, HIGH);
digitalWrite(dPin, LOW);
digitalWrite(ePin, LOW);
digitalWrite(fPin, HIGH);
digitalWrite(gPin, HIGH);
digitalWrite(dpPin, LOW);
break;
case FIVE:
digitalWrite(aPin, HIGH);
digitalWrite(bPin, LOW);
digitalWrite(cPin, HIGH);
digitalWrite(dPin, HIGH);
digitalWrite(ePin, LOW);
digitalWrite(fPin, HIGH);
digitalWrite(gPin, HIGH);
digitalWrite(dpPin, LOW);
break;
case SIX:
digitalWrite(aPin, HIGH);
digitalWrite(bPin, LOW);
digitalWrite(cPin, HIGH);
digitalWrite(dPin, HIGH);
digitalWrite(ePin, HIGH);
digitalWrite(fPin, HIGH);
digitalWrite(gPin, HIGH);
digitalWrite(dpPin, LOW);
break;
case SEVEN:
digitalWrite(aPin, HIGH);
digitalWrite(bPin, HIGH);
digitalWrite(cPin, HIGH);
digitalWrite(dPin, LOW);
digitalWrite(ePin, LOW);
digitalWrite(fPin, LOW);
digitalWrite(gPin, LOW);
digitalWrite(dpPin, LOW);
break;
case EIGHT:
digitalWrite(aPin, HIGH);
digitalWrite(bPin, HIGH);
digitalWrite(cPin, HIGH);
digitalWrite(dPin, HIGH);
digitalWrite(ePin, HIGH);
digitalWrite(fPin, HIGH);
digitalWrite(gPin, HIGH);
digitalWrite(dpPin, LOW);
break;
case NINE:
digitalWrite(aPin, HIGH);
digitalWrite(bPin, HIGH);
digitalWrite(cPin, HIGH);
digitalWrite(dPin, LOW);
digitalWrite(ePin, LOW);
digitalWrite(fPin, HIGH);
digitalWrite(gPin, HIGH);
digitalWrite(dpPin, LOW);
break;
case DECIMAL_POINT:
digitalWrite(aPin, LOW);
digitalWrite(bPin, LOW);
digitalWrite(cPin, LOW);
digitalWrite(dPin, LOW);
digitalWrite(ePin, LOW);
digitalWrite(fPin, LOW);
digitalWrite(gPin, LOW);
digitalWrite(dpPin, HIGH);
break;
default:
digitalWrite(aPin, LOW);
digitalWrite(bPin, LOW);
digitalWrite(cPin, LOW);
digitalWrite(dPin, LOW);
digitalWrite(ePin, LOW);
digitalWrite(fPin, LOW);
digitalWrite(gPin, LOW);
digitalWrite(dpPin, LOW);

}
}

void LEDDisplay::DisplayNumber (int number){

int temp;

// determine the digits of the number

int thousand = number/1000;
temp = number%1000;
int hundred = temp/100;
temp = temp%100;
int ten = temp/10 ;
temp = temp%10;
int unit = temp;

// determine what to display (note I cast int to Num)

if (thousand == 0){
if (hundred == 0){
if (ten == 0){
digitalWrite(y1Pin, HIGH);
digitalWrite(y2Pin, HIGH);
digitalWrite(y3Pin, HIGH);
digitalWrite(y4Pin, LOW);
DisplayDigit((Num)unit);
delay(5);
}
else {
digitalWrite(y1Pin, HIGH);
digitalWrite(y2Pin, HIGH);
digitalWrite(y3Pin, LOW);
DisplayDigit((Num)ten);
delay(5);
digitalWrite(y3Pin, HIGH);
digitalWrite(y4Pin, LOW);
DisplayDigit((Num)unit);
delay(5);
digitalWrite(y4Pin, HIGH);
}
}
else{
digitalWrite(y1Pin, HIGH);
digitalWrite(y2Pin, LOW);
DisplayDigit((Num)hundred);
delay(5);
digitalWrite(y2Pin, HIGH);
digitalWrite(y3Pin, LOW);
DisplayDigit((Num)ten);
delay(5);
digitalWrite(y3Pin, HIGH);
digitalWrite(y4Pin, LOW);
DisplayDigit((Num)unit);
delay(5);
digitalWrite(y4Pin, HIGH);
}
}
else{
digitalWrite(y1Pin, LOW);
DisplayDigit((Num)thousand);
delay(5);
digitalWrite(y1Pin, HIGH);
digitalWrite(y2Pin, LOW);
DisplayDigit((Num)hundred);
delay(5);
digitalWrite(y2Pin, HIGH);
digitalWrite(y3Pin, LOW);
DisplayDigit((Num)ten);
delay(5);
digitalWrite(y3Pin, HIGH);
digitalWrite(y4Pin, LOW);
DisplayDigit((Num)unit);
delay(5);
digitalWrite(y4Pin, HIGH);
}

}
