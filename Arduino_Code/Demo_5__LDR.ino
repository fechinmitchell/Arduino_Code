int sensePin = 0;


void setup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(sensePin));
  delay(500);
}
