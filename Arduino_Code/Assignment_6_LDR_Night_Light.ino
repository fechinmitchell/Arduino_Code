
int sensePin = 0;
int ledPin = 9;


void setup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);

  pinMode(ledPin, OUTPUT);



}

void loop() {

  int val = analogRead(sensePin);

  if (val < 800) digitalWrite(ledPin, LOW);
  else digitalWrite(ledPin, HIGH);
}
