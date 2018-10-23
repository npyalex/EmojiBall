#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

const int angryPin = 7;
int xAccel;
int yAccel;
int zAccel;
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

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Acceleration Test");

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


void loop(void)
{
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

/*  Serial.print("-20.,"); //set lower scale
  Serial.print(v.x());  //x acceleration
  Serial.print(",");
  Serial.print(v.y()); //y accel
  Serial.print(",");
  Serial.print(v.z()); //z accel
  Serial.println(",20.0"); //set upper scale
*/  
 if(millis()-lastRead>=sampleRate){ //some delay before it becomes calm again
   /*if the acceleraction is above a threshold, become angry*/
  if ((xAccel>threshold)||(xAccel<-threshold)||(yAccel>threshold)||(yAccel<-threshold)||(zAccel>threshold)||(zAccel<-threshold)){
    (angry = true);
  } else {
    (angry = false);
  }
  if (angry==true){
    Serial.println("Don't move me so fast!");
    digitalWrite (angryPin,HIGH);
  } else  {
    Serial.println("I am calm");
    digitalWrite (angryPin,LOW);
    (angry = false);
  }
  /* Display calibration status for each sensor.
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
    }
    Serial.println();
  */

  delay(BNO055_SAMPLERATE_DELAY_MS);
  lastRead = millis();
 }
}
