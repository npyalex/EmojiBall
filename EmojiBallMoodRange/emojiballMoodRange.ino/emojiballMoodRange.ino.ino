//initialize Pin 8 as the pin that controls the green LEDs
const int greenPin = 8;
//initialize Pin 7 as the pin that controls the red LEDs.
const int redPin = 7;
//initialize Pin 6 as the pin that controls the yellow LEDs.
const int yellowPin = 6;
//initialize Pin 5 as the pin that controls the blue LEDs.
const int bluePin = 5;

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

  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);  
}

void loop() {
  // TODO - Handle changing start to true
  isGameStarted = true;
  
  if(isGameStarted){
    // Game Started - Check for inputs
    checkLight();
    Serial.println(moodPoints);
    if(moodPoints <= 1000 && moodPoints > 750){
      // Happy Zone
      digitalWrite(greenPin,HIGH);
      digitalWrite(redPin,LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(bluePin, LOW);
    } else if(moodPoints <= 750 && moodPoints > 250){
      // Calm Zone
      digitalWrite(greenPin,LOW);
      digitalWrite(redPin,LOW);
      digitalWrite(yellowPin, HIGH);
      digitalWrite(bluePin, LOW);
    } else if(moodPoints <= 250 && moodPoints >= 0){
      // Mad Zone
      digitalWrite(greenPin,LOW);
      digitalWrite(redPin,HIGH);
      digitalWrite(yellowPin, LOW);
      digitalWrite(bluePin, LOW);
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
    
    if(moodPoints = 1000){
      moodPoints = 1000;
    } else {
      moodPoints += 10;
    }
    
  } else {
    // Light is dim, lose mood points, min points 0
    
    if(moodPoints <= 0){
      moodPoints = 0;
    } else {
      moodPoints -= 10;
    }
    
    // moodPoints -=10;
  }
}
