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
    checkOrient();
    Serial.println("--------------------------");
    String mp = String(moodPoints);
    Serial.println("--------------------------" + mp);
    Serial.println("--------------------------");
    if(moodPoints <= 1000 && moodPoints > 750){
      // Happy Zone
      getHappy();
    } else if(moodPoints <= 750 && moodPoints > 250){
      // Calm Zone
      getCalm();
    } else if(moodPoints <= 250 && moodPoints >= 0){
      // Mad Zone
      getMad();
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
      moodPoints += 10;
    }   
  } else {
    // Light is dim, lose mood points, min points 0
    // moodPoints -=10;
    if(moodPoints <= 0){
      moodPoints = 0;
    } else {
      moodPoints -= 10;
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
void getMad(){
  digitalWrite(greenPin,LOW);
  digitalWrite(redPin,HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(bluePin, LOW);
  makeASound("mad");
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
  } else if(mood.equals("calm")){
    Serial.println("Calm Song");
  } else if (mood.equals("mad")){
    Serial.println("Mad Song");
  } else {
    Serial.println("Ooops! Mood is undefined");
  }
}

/*
 * Check the balls orientation
 */
void checkOrient(){
  // TODO Check the orientation of the ball
 }
