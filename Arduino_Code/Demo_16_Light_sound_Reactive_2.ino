const int ledPin =  12;      // the number of the LED pin
const int thresholdvalue=400;//The threshold to turn the led on
void setup() {
     pinMode(ledPin, OUTPUT); 
}
 
void loop() {
  int sensorValue = analogRead(A0);//use A0 to read the electrical signal
  if(sensorValue>thresholdvalue)
  digitalWrite(ledPin,HIGH);//if the value read from A0 is larger than 400,then light the LED
  delay(20);
  digitalWrite(ledPin,LOW);
}
