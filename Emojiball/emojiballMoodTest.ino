const int greenPin = 8;
const int redPin = 7;

int ballMood = 1;

void setup() {
  // put your setup code here, to run once:
pinMode(greenPin, OUTPUT);
pinMode(redPin, OUTPUT);
  // initialize serial communication at 9600 bits per second:
Serial.begin(9600);  
}

void loop() {

// read the input on analog pin 0:
int sensorValue = analogRead(A0);
// print out the value you read in the monitor:
Serial.println(sensorValue);
delay(1);        // delay in between reads for stability
  
// bright light makes the ball happy
 if (sensorValue>200){
  ballMood = 1;
    } else {
  ballMood = 0;
    }
// happy ball, green light
  if (ballMood == 1){
    digitalWrite(greenPin,HIGH);
    digitalWrite(redPin,LOW);
    } else {
  //grumpy ball, red light
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
  }
}
