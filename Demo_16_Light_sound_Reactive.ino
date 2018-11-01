int DO = 2; //Pin for Digital Output - DO
int DA = A0; // Pin for Analog Output - AO
int threshold = 320; //Set minimum threshold for LED litint 
int threshold_1 = 325; //Set minimum threshold for LED lit
int threshold_2 = 330; //Set minimum threshold for LED lit
int threshold_3 = 335; //Set minimum threshold for LED lit
int threshold_4 = 340; //Set minimum threshold for LED lit
int threshold_5 = 345; //Set minimum threshold for LED lit

int sensorvalue = 0;
 
void setup() {
  Serial.begin(5z600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}
 
void loop() {
  sensorvalue = analogRead(DA);  //Read the analog value
  Serial.print("Analog: ");
  Serial.print(sensorvalue);  //Print the analog value
  Serial.print("  ");
  Serial.print("Digital: ");
  Serial.println(digitalRead(DO));  //Print the digital value
 
  if (sensorvalue >= threshold) { //Compare analog value with threshold
    digitalWrite(3, HIGH);
  }
  else {
    digitalWrite(3, LOW);
  }
    if (sensorvalue >= threshold_1) { //Compare analog value with threshold
    digitalWrite(4, HIGH);
  }
  else {
    digitalWrite(4, LOW);
  }
    if (sensorvalue >= threshold_2) { //Comparee analog value with threshold
    digitalWrite(5, HIGH);
  }
  else {
    digitalWrite(5, LOW);
  }
    if (sensorvalue >= threshold_3) { //Compare analog value with threshold
    digitalWrite(6, HIGH);
  }
  else {
    digitalWrite(6, LOW);
  }
    if (sensorvalue >= threshold_4) { //Compare analog value with threshold
    digitalWrite(7, HIGH);
  }
  else {
    digitalWrite(7, LOW);
  }
    if (sensorvalue >= threshold_5) { //Compare analog value with threshold
    digitalWrite(8, HIGH);
  }
  else {
    digitalWrite(8, LOW);
  }
}
