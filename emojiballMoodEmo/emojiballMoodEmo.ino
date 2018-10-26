/*
 * Melody Code provided from code by Tom Igoe
 * http://www.arduino.cc/en/Tutorial/Tone
 */
 /*
  * Orientation Code provided by Adafruit [CITATION NEEDED]
  */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include "pitches.h"
//notes in the melody
int angryTune[] = { NOTE_CS8, NOTE_CS8, NOTE_CS8 };
int happyTune[] = { NOTE_F6, NOTE_DS6, NOTE_CS6, NOTE_DS6, NOTE_CS6 };
int calmTune[] = { NOTE_C4, 0, NOTE_C4, NOTE_G4, 0, NOTE_G4, NOTE_A4, 0, NOTE_A4, NOTE_G4 };
//note durations: 2 = half note, 4 = quarter note, 8 = eighth note
int angryNoteDuration[] = {2, 2, 2};
int happyNoteDuration[] = {8, 16, 8, 8, 2};
int calmNoteDuration[] = {8, 16, 8, 8, 16, 8, 8, 16, 8, 2};

//initialize Pin 8 as the pin that controls the green LEDs
const int greenPin = 8;
//initialize Pin 7 as the pin that controls the red LEDs.
const int redPin = 7;
//initialize Pin 6 as the pin that controls the yellow LEDs.
const int yellowPin = 6;
//initialize Pin 5 as the pin that controls the blue LEDs.
const int bluePin = 5;
//intialize Pin 4 as the speaker pin
const int speakerPin = 4;
//intialize Pin 3 as the orientation pin
//const int orientPin = 3;
int xAccel, yAccel, zAccel;
bool angry = false;
int threshold = 2;

int sampleRate = 500;
unsigned long lastRead;
/* This driver reads the "linear acceleration" (gravity subtracted from the BNO055 raw acceleration) and outputs data for the Arduino Serial Plotter
   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground
   History
   =======
   2015/MAR/03  - First release (KTOWN)
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055();
imu::Vector<3> v;

/*
    Arduino setup function (automatically called at startup)
*/

// Global var to keep score of points - initialised at 500 (mid calm). Mood range is 0 to 1000
int moodPoints = 500;

boolean isGameStarted = false;

void setup() {
  //greenPin is an output
  pinMode(greenPin, OUTPUT);
  
  //redPin is an output
  pinMode(redPin, OUTPUT);
  
  //yellowPin is an output
  pinMode(yellowPin, OUTPUT);
  
  //bluePin is an output
  pinMode(bluePin, OUTPUT);
  
  //speaker
  pinMode(4, INPUT_PULLUP);

  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);  

  /* Initialise the sensor */
  
  if (!bno.begin())
  { 
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);
  bno.setExtCrystalUse(true);
}

void loop() {
  // TODO - Handle changing start to true
  isGameStarted = true;
  
  if(isGameStarted){    
    // Game Started - Check for inputs
    // Game Started - Check the orientation
    checkLight();
    checkOrient();
    Serial.println("--------------------------");
    String mp = String(moodPoints);
    Serial.println("---------- Mood Points" + mp);
    Serial.println("--------------------------");
    if(moodPoints <= 1000 && moodPoints > 750){
      // Happy Zone
      getHappy();
    } else if(moodPoints <= 750 && moodPoints > 250){
      // Calm Zone
      getCalm();
    } else if(moodPoints <= 250 && moodPoints >= 0){
      // Mad Zone
      getAngry();
    } else  {
      // Error occured
      Serial.println("Error with mood points range");
    }
    delay(50);
  } else {
    // Game not started, neutral light?
  }
}

/*
 * This function gets the light reading when game starts
 * Sensor is at pin A0
 * Checks the value to determine dim or bright room
 * Uses value to determine scored or lost mood point
 */
void checkLight(){
  int lightVal = analogRead(A0);
  // print out the value in the monitor:
  Serial.println(lightVal);
  delay(1); // delay in between reads for stability
  if(lightVal > 500){
    // Light is bright, score mood points, max points 1000
    // moodPoints += 10;  
    if(moodPoints >= 1000){
      moodPoints = 1000;
    } else {
      moodPoints += 50;
    }   
  } else {
    // Light is dim, lose mood points, min points 0
    // moodPoints -=10;
    if(moodPoints <= 0){
      moodPoints = 0;
    } else {
      moodPoints -= 50;
    }
  }
}

/*
 * Make the ball Happy
 * Turns on green LED & turns off the rest. 
 * Pass 'happy' mood to makeASound()
 */
void getHappy(){
  //TODO Check the degree of happiness
  digitalWrite(greenPin,HIGH);
  digitalWrite(redPin,LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(bluePin, LOW);
  makeASound("happy");
}

/*
 * Make the ball Mad
 * Turns on red LED & turns off the rest. 
 * Pass 'mad' mood to makeASound()
 */
void getAngry(){
  digitalWrite(greenPin,LOW);
  digitalWrite(redPin,HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(bluePin, LOW);
  makeASound("angry");
}

/*
 * Make the ball Calm
 * Turns on yellow LED & turns off the rest. 
 * Pass 'calm' mood to makeASound()
 */
void getCalm(){
  digitalWrite(greenPin,LOW);
  digitalWrite(redPin,LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(bluePin, LOW);
  makeASound("calm");
}

/*
 * Make a sound depending on the mood
 */
void makeASound(String mood){
  // TODO Check the mood & play a sound
  if(mood.equals("happy")){
    Serial.println("Happy Song"); 
    for (int thisNote = 0; thisNote < 5; thisNote++) {  
      int noteDuration = 2000 / happyNoteDuration[thisNote];
      tone(speakerPin, happyTune[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(speakerPin);
    }   
  } else if(mood.equals("calm")){
    Serial.println("Calm Song");
    for (int thisNote = 0; thisNote < 10; thisNote++) {  
      int noteDuration = 1500 / calmNoteDuration[thisNote];
      tone(speakerPin, calmTune[thisNote], noteDuration);
  
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(speakerPin);
    }
  } else if (mood.equals("angry")){
    Serial.println("Angry Song");
    for (int thisNote = 0; thisNote < 3; thisNote++) {  
      int noteDuration = 2000 / angryNoteDuration[thisNote];
      tone(speakerPin, angryTune[thisNote], noteDuration);
  
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(speakerPin);
    }
  } else {
    Serial.println("Ooops! Mood is undefined");
  }
}

/*
 * Check the balls orientation
 */
void checkOrient(){
  // TODO Check the orientation of the ball
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  
  v = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  xAccel = (v.x());
  yAccel = (v.y());
  zAccel = (v.z());
  
  
  /* Display the floating point data */

  /*  
  Serial.print("-20.,"); //set lower scale
  Serial.print(v.x());  //x acceleration
  Serial.print(",");
  Serial.print(v.y()); //y accel
  Serial.print(",");
  Serial.print(v.z()); //z accel
  Serial.println(",20.0"); //set upper scale
  */ 
 
  if(millis()-lastRead>=sampleRate){ 
    //some delay before it becomes calm again
    /*if the acceleraction is above a threshold, become angry*/
    if ((xAccel>threshold)||(xAccel<-threshold)||(yAccel>threshold)||(yAccel<-threshold)||(zAccel>threshold)||(zAccel<-threshold)){
      angry = true;
    } else {
      angry = false;
    }
    
    if (angry==true){
      Serial.println("Don't move me so fast!");
      moodPoints -= 150;
    } else {
      Serial.println("I am calm");
      moodPoints += 200;
      angry = false;
    }

  /*
    Display calibration status for each sensor.
    uint8_t system, gyro, accel, mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);
    if (gyro+accel+mag != 9) { //not yet calibrated
      Serial.print("CALIBRATION: Sys=");
      Serial.print(system, DEC);
      Serial.print(" G=");
      Serial.print(gyro, DEC);
      Serial.print(" A=");
      Serial.print(accel, DEC);
      Serial.print(" M=");
      Serial.print(mag, DEC);
    } */
    Serial.println();


    delay(BNO055_SAMPLERATE_DELAY_MS);
    lastRead = millis();
  }
 }
