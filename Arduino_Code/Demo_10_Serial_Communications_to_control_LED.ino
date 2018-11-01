void setup() {
  // create serial object
  Serial.begin(9600);
}

void loop() {
  //have the arduino wait to receive input
  while ( Serial . available() == 0);
  
  //read the input
  int val = Serial.read() - '0';
  
  //echo the input
  Serial.println(val);
  
}
