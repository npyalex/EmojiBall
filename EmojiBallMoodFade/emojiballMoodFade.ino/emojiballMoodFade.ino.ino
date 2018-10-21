//initialize Pin 8 as the pin that controls the green LEDs
const int greenPin = 8;
//initialize Pin 7 as the pin that controls the red LEDs.
const int redPin = 7;
//initialize Pin 6 as the pin that controls the yellow LEDs.
const int yellowPin = 6;
//initialize Pin 5 as the pin that controls the blue LEDs.
const int bluePin = 5;

//initialize the ballMood variable
int ballMood = 1;
//initialize currentMood variable as a CALM ball - can only be between -1000 and 1000
int currentMood = 0;
//intilize the lightVal variable
int lightVal = 0;
//initialize the fadeVal variable
int fadeVal = 10;
//boolean to check whether light is fading
boolean isFading = false;

void setup() {

//greenPin is an output
pinMode(greenPin, OUTPUT);
//redPin is an output
pinMode(redPin, OUTPUT);
//yellowPin is an output
pinMode(yellowPin, OUTPUT);
//bluePin is an output
pinMode(bluePin, OUTPUT);

// initialize serial communication at 9600 bits per second
Serial.begin(9600);  

  // Get the intial light reading when game starts
  // Read the input from the light sensor on analog pin 0:
  int initLight = analogRead(A0);
  // print out the value in the monitor:
  Serial.println(initLight);
  delay(1); // delay in between reads for stability

  if(initLight > 500){
    // Light is bright, ball in HAPPY zone, fading is -ve
    isFading = true;
    Serial.println("Is Fading");
  } else {
    // Light is dim, ball in MAD zone, set fadeVal to +ve
    isFading = false;
  }
}

void loop() {
  if(isFading){
    // Happy zone - reduce mood
    Serial.println("Happy Zone");
    int fadeVal = 1000;
    for(fadeVal; fadeVal >= 750; fadeVal -=10) {
      // Countdown from 1000 to 750; - Happy Zone
      Serial.println("Happy Zone");
      analogWrite(greenPin, 255);
      analogWrite(yellowPin, 0);
      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
      delay(30);
    }
    
    for(fadeVal; fadeVal >=250; fadeVal -=10) {
      // Countdown from 749 to 250 - Calm Zone
      Serial.println("Calm Zone");
      analogWrite(greenPin, 0);
      analogWrite(yellowPin, 255);
      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
      delay(30);
    }

    for(fadeVal; fadeVal >=0; fadeVal -=10) {
      // Countdown from 249 to 0 - Mad Zone
      Serial.println("Mad Zone");
      analogWrite(greenPin, 0);
      analogWrite(yellowPin, 0);
      analogWrite(redPin, 255);
      analogWrite(bluePin, 0);
      delay(30);
    }

    // Done fading mood, so start brightening mood
    isFading = false;
    Serial.println(" ");
    Serial.println("Done fading -- brightening now --");
    Serial.println(" ");    
  } else {
    int fadeVal = 0;
    for(fadeVal; fadeVal < 250; fadeVal +=10){
      // Count up from 0 to 249 - Mad Zone
      Serial.println("Mad Zone");
      analogWrite(greenPin, 0);
      analogWrite(yellowPin, 0);
      analogWrite(redPin, 255);
      analogWrite(bluePin, 0);
      delay(30);
    }

    for(fadeVal; fadeVal < 750; fadeVal +=10){
      // Count up from 250 to 749 - Calm Zone
      Serial.println("Calm Zone");
      analogWrite(greenPin, 0);
      analogWrite(yellowPin, 255);
      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
      delay(30);
    }

    for(fadeVal; fadeVal <=1000; fadeVal +=10){
      // Count up from 750 to 1000 - Happy Zone
      Serial.println("Happy Zone");
      analogWrite(greenPin, 255);
      analogWrite(yellowPin, 0);
      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
      delay(30);
    }

    // Done brightening mood, so start fading again
    isFading = true;
    Serial.println(" ");
    Serial.println("Done brightening -- fading now --");
    Serial.println(" ");
  }
}
