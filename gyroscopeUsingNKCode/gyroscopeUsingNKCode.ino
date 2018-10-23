/*
 * Creation & Computation - Digital Futures, OCAD University
 * Kate Hartman / Nick Puckett
 * 
 * Orientation Sensor: https://github.com/adafruit/Adafruit_Sensor
 * Simple Read and print of the X Y Z angles of orientation in degrees 
 * For Arduino Micro
 * O Sensor       Arduino
 * SDA*            D2            
 * SCL*            D3
 * 
 * *You must connect a 4.7K resistor between the SDA connection on the sensor and +5V
 * *You must connect a 4.7K resistor between the SCL connection on the sensor and +5V
 * 
 */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 orientationSensor = Adafruit_BNO055();  //create a orienation sensor object


unsigned long lastRead;   //used for the sampleRate timer
const int angryPin = 7;
int sampleRate = 100;     //the sampleRate for reading the sensor.  Without this it will crash.

/*
float xOrientation;     //holds the X orientation    Degrees
float yOrientation;     //holds the Y orientation    Degrees
float zOrientation;      //holds the Z orientation   Degrees
*/
float xAccel;    //holds the X accelleration m/s^2
float yAccel;    //holds the Y accelleration m/s^2
float zAccel;    //holds the Z acceleration  m/s^2

void setup() 
{
  Serial.begin(9600);
  
  
  if(!orientationSensor.begin()) //connect to the sensor and print an error if there is a problem
  {
  
    Serial.println("Can't connect to the Sensor. Check the Wiring");
    while(1);
  }
  
  delay(1000);  ///wait for one second for everything to start up.
    
  orientationSensor.setExtCrystalUse(true);
}

void loop() 
{
 
  if(millis()-lastRead>=sampleRate)
  {

 // v = orientationSensor.getVector(Adafruit_BNO55::VECTOR_LINEARACCEL);
  
  sensors_event_t event; //create an event variable
  orientationSensor.getEvent(&event); //pass it to the BNO055 object

  //get the values
  xAccel = event.orientation.x;
  yAccel = event.orientation.y;
  zAccel = event.orientation.z;
   
  
  //print the data
  Serial.print("X: ");
  Serial.print(xAccel);
  Serial.print("  Y:  ");
  Serial.print(yAccel);
  Serial.print("  Z:  ");
  Serial.println(zAccel);

  

  
  lastRead = millis(); //save the value of the current time so the timer works
  }
}
