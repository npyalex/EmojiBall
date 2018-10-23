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

// read the input from the light sensor on analog pin 0:
int sensorValue = analogRead(A0);
// print out the value in the monitor:
Serial.println(sensorValue);
delay(1);        // delay in between reads for stability
  
  // bright light makes the ball happy
  if (sensorValue>600){
    // Ball in bright light - get HAPPY
    ballMood = 0;
  } else if(sensorValue>400 && sensorValue<600) {
    // Ball in medium light - get CALM
    ballMood = 1;
  } else if(sensorValue>200 && sensorValue<400) {
    // Ball in dim light - get SAD
    ballMood = 2; 
  } else {
    // Ball in darkness - get MAD
    ballMood = 3;
  }

  // Using the ballMood indicator, turn on appropriate light, turn off other lights
  // happy ball makes green light
  if (ballMood == 0){
    digitalWrite(greenPin,HIGH);
    digitalWrite(redPin,LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(bluePin, LOW);
  } else if(ballMood == 1) {
    // calm ball makes yellow light
    digitalWrite(greenPin,LOW);
    digitalWrite(redPin,LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(bluePin, LOW);
  } else if(ballMood == 2) {
    // sad ball makes blue light
    digitalWrite(greenPin,LOW);
    digitalWrite(redPin,LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(bluePin, HIGH);
  } else if(ballMood == 3) {
    // angry ball makes red light
    digitalWrite(greenPin,LOW);
    digitalWrite(redPin,HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(bluePin, LOW);
  }
}
