
int buttonPin = 8;

void setup() {
  
  // sets the button pin as an input
  pinMode(buttonPin, INPUT);

  //allow us to listen to serial communiction from the arduino
  Serial.begin(9600);
  
}

void loop() {
  // print the buton state to a serial terminal
  Serial.println(digitalRead(buttonPin));
  delay(1000);
  //wait one second, then print again.  
}
