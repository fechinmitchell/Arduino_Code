#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>

//analogue Input Sensors
int Sensor0 = A0;
int Sensor1 = A1;
int Sensor2 = A2;
int Sensor3 = A3;
int Sensor4 = A4;
int Sensor5 = A5;

//Piezo Disc
byte PiezoDisc1 = 0;
byte PiezoDisc2 = 0;
byte PiezoDisc3 = 0;
byte PiezoDisc4 = 0;
byte PiezoDisc5 = 0;
byte PiezoDisc6 = 0;
int THRESHOLD = 100;

int velocity = 100;
int noteON = 144;
int noteOFF = 128;
int note0 = 60;
int note1 = 62;
int note2 = 64;
int note3 = 65;
int note4 = 67;
int note5 = 69;
void setup()
{
 
  Serial.begin(115200);
}
void loop()
{
 PiezoDisc1 = analogRead(Sensor0);
  if (PiezoDisc1 >= THRESHOLD)
  {

    MIDImessage(noteON, note0, velocity);//turn note on
    delay(200);//hold note for 300ms
    MIDImessage(noteOFF, note0, velocity);//turn note off
    delay(100);//wait 200ms until triggering next note
  }
    PiezoDisc2 = analogRead(Sensor1);
    if (PiezoDisc2 >= THRESHOLD)
  {

    MIDImessage(noteON, note1, velocity);//turn note on
    delay(200);//hold note for 300ms
    MIDImessage(noteOFF, note1, velocity);//turn note off
    delay(100);//wait 200ms until triggering next note
  
  }

   PiezoDisc3 = analogRead(Sensor2);
    if (PiezoDisc3 >= THRESHOLD)
  {

    MIDImessage(noteON, note2, velocity);//turn note on
    delay(200);//hold note for 300ms
    MIDImessage(noteOFF, note2, velocity);//turn note off
    delay(100);//wait 200ms until triggering next note
  
  }


    PiezoDisc4 = analogRead(Sensor3);
    if (PiezoDisc4 >= THRESHOLD)
   {

    MIDImessage(noteON, note3, velocity);//turn note on
    delay(200);//hold note for 300ms
    MIDImessage(noteOFF, note3, velocity);//turn note off
    delay(100);//wait 200ms until triggering next note
  
  }


    PiezoDisc5 = analogRead(Sensor4);
    if (PiezoDisc5 >= THRESHOLD)
  {

    MIDImessage(noteON, note4, velocity);//turn note on
    delay(200);//hold note for 300ms
    MIDImessage(noteOFF, note4, velocity);//turn note off
    delay(100);//wait 200ms until triggering next note
  
  }


    PiezoDisc6 = analogRead(Sensor5);
    if (PiezoDisc6 >= THRESHOLD)
  {

    MIDImessage(noteON, note5, velocity);//turn note on
    delay(200);//hold note for 300ms
    MIDImessage(noteOFF, note5, velocity);//turn note off
    delay(100);//wait 200ms until triggering next note
  
  }
}

//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send vel
