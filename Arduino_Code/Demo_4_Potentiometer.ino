
int potPin = 8;

void setup() {
  
  // sets the button pin as an input
  pinMode(potPin, INPUT);

  //allow us to listen to serial communiction from the arduino
  Serial.begin(9600);
  
}

void loop() {
  // print the buton state to a serial terminal
  Serial.println(analogRead(potPin));
  delay(1000);
  //wait one second, then print again.  
}
