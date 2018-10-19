//initialize Pin 8 as the pin that controls the green LEDs
const int greenPin = 8;
//initialize Pin 7 as the pin that controls the red LEDs.
const int redPin = 7;

//initialize the ballMood variable
int ballMood = 1;

void setup() {

//greenPin is an output
pinMode(greenPin, OUTPUT);
//redPin is an output
pinMode(redPin, OUTPUT);
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
 if (sensorValue>200){
  ballMood = 1;
    } else {
  ballMood = 0;
    }
// happy ball makes green light
  if (ballMood == 1){
    digitalWrite(greenPin,HIGH);
    digitalWrite(redPin,LOW);
    } else {
  //grumpy ball makes red light
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
  }
}
