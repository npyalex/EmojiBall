/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"

// notes in the melody:
int melody[] = {

 NOTE_CS8, NOTE_CS8, NOTE_CS8 // ALARM for ANGRY

    
 // NOTE_F6, NOTE_DS6, NOTE_CS6, NOTE_DS6, NOTE_CS6 // HAPPY I GUESS
  
 // NOTE_CS7, NOTE_G7, NOTE_AS7, NOTE_G7, NOTE_CS8 // ANNOYED/ANGRY
 
 // NOTE_C4, 0, NOTE_C4, NOTE_G4, 0, NOTE_G4, NOTE_A4, 0, NOTE_A4, NOTE_G4 = TWINKLE TWINKLE
        
 // NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, 0, 0, NOTE_G5, 0, NOTE_G4 = MARIO TUNE
 
 // NOTE_DS8, NOTE_D8, NOTE_CS8, NOTE_C8, NOTE_B7: EAR PIERCING HIGH NOISES
 // NOTE_AS7, NOTE_A7, NOTE_GS7, NOTE_G7, NOTE_FS7: AS7 is piercing, the rest are high
 // NOTE_F7, NOTE_E7, NOTE_DS7, NOTE_D7, NOTE_CS7: ok high pierce
 // NOTE_C7, NOTE_B6, NOTE_AS6, NOTE_A6, NOTE_GS6: moderate high pierce
 // NOTE_G6, NOTE_FS6, NOTE_F6, NOTE_E6, NOTE_DS6: good not so piercing high
 // NOTE_D6, NOTE_CS6, NOTE_C6, NOTE_B5, NOTE_AS5: high medium range
 // NOTE_A5, NOTE_GS5, NOTE_G5, NOTE_FS5, NOTE_F5: medium range
 // NOTE_E5, NOTE_DS5, NOTE_D5, NOTE_CS5, NOTE_C5: medium lower
 // NOTE_B4, NOTE_AS4, NOTE_A4, NOTE_GS4, NOTE_G4: ultimate medium

 // NOTE_FS4, NOTE_F4, NOTE_E4, NOTE_DS4, NOTE_D4, NOTE_CS4, NOTE_C4*middle C, NOTE_B3: THE medium range
 
 // NOTE_FS3, NOTE_G3, NOTE_GS3, NOTE_A3, NOTE_AS3: higher range
 // NOTE_CS3, NOTE_D3, NOTE_DS3, NOTE_E3, NOTE_F3: we in the medium range 
 // NOTE_GS2, NOTE_A2, NOTE_AS2, NOTE_B2, NOTE_C3: nicer buzzery sounds
 // NOTE_DS2, NOTE_E2, NOTE_F2, NOTE_FS2, NOTE_G2: higher buzzery sounds
 // NOTE_AS1, NOTE_B1, NOTE_C2, NOTE_CS2, NOTE_D2: more buzzery sounds - nice sounds. This and lower for sad
 // NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1: half higher
 // NOTE_B0, NOTE_C1, NOTE_CS1, NOTE_D1, NOTE_DS1: low notes
 
};

int noteDurations[] = {
  2, 2, 2
  
  // 8, 16, 8, 8, 2
};

void setup() {
    pinMode(3, INPUT_PULLUP);

    PlayTune();
   // iterate over the notes of the melody:
  }

void loop() {
  if (!digitalRead(3)){
    PlayTune();
  }
  // no need to repeat the melody.
}

void PlayTune()
  {
    for (int thisNote = 0; thisNote < 3; thisNote++) {  

    int noteDuration = 2000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    }
  }
