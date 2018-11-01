#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <Wire.h>
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high

float sAccel;
float eAccel;
float sTime;
float eTime;

float FinalTime;
float FinalAccel;

float velocity;
float distance;
float weightSize;
float gravity1 = 9.81;
double force;
float bicepLen = 0.04;
double work;
float roarm;
double trueWeight;
double power;
double torque;

float mock;

#define OUTPUT_READABLE_YAWPITCHROLL
#define OUTPUT_READABLE_WORLDACCEL


#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;
const int ledPin6 = 6;
const int ledPin7 = 7;
int ledState = LOW ;
long previousMillis = 0;
long interval = 1000;
long startTime = 0;
long elapsedTime ;                  // elapsed time for stop watch
long resetTime ;





// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector



// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
  mpuInterrupt = true;
}



// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  Serial.begin(115200);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // wait for ready
  Serial.println(F("\nSend any character to begin DMP programming and demo: "));
  while (Serial.available() && Serial.read()); // empty buffer
  while (!Serial.available());                 // wait for data
  while (Serial.available() && Serial.read()); // empty buffer again

  // load and configure the DMP
  Serial.println(F("Initializing DMP..."));
  devStatus = mpu.dmpInitialize();

  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }

  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
}

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {

  // if programming failed, don't try to do anything
  if (!dmpReady) return;

  // wait for MPU interrupt or extra packet(s) available
  while (!mpuInterrupt && fifoCount < packetSize) {
  }

  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);

    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;

    OUTPUT_READABLE_YAWPITCHROLL
    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    //       Serial.print("ypr\t");
    //       Serial.print(ypr[0] * 180/M_PI);
    //       Serial.print("\t");
    //       Serial.print(ypr[1] * 180/M_PI);
    //       Serial.print("\t");
    //       Serial.println(ypr[2] * 180/M_PI);

    OUTPUT_READABLE_WORLDACCEL
    // display initial world-frame acceleration, adjusted to remove gravity
    // and rotated based on known orientation from quaternion
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetAccel(&aa, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
    mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
    //            Serial.print("aworld\t");
    //            Serial.print(aaWorld.x);
    //            Serial.print("\t");
    //            Serial.print(aaWorld.y);
    //            Serial.print("\t");
    //            Serial.println(aaWorld.z);
  }

  if ( ypr[2] * 180 / M_PI > 10 && ypr[2] * 180 / M_PI < 40  ) {
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin6, ledState);
  }
  else {
    digitalWrite(ledPin6, LOW); // this turns this led off, beacuse we want to blink another led
  }

  if (ypr[2] * 180 / M_PI > 60) {
    Serial.write("\t");
    Serial.write("Finished Calculating:\t");
    Serial.write("\t");    
      while (ypr[2] * 180 / M_PI > 60.8) {
         mpu.setDMPEnabled(false);
         Serial.write("\n Please Enter any Value to Start Calculations: \n");
          while (Serial.available() == 0.0) {
           }
          mock = Serial.parseFloat();

         Serial.write("Please Enter Starting Acceleration: \n");
          while (Serial.available() == 0.0) {
           }
          sAccel = Serial.parseFloat();
          Serial.write("Starting Acceleration: ");
          Serial.print(sAccel);

            //Stops skipping the Serial Inputs
            Serial.println("....");
            while (Serial.available() == 0.0) {
            }
            mock = Serial.parseFloat();

        Serial.write("\nPlease Enter Ending Acceleration: \n");
          while (Serial.available() == 0.0) {
            }
          eAccel = Serial.parseFloat();
          Serial.write("Ending Acceleration: ");
          Serial.print(eAccel);

          FinalAccel = (eAccel - sAccel)/10;
          Serial.print("\n");
          Serial.write("Final Acceleration: ");
          Serial.print(FinalAccel);
          Serial.print("\n");

            //Stops skipping the Serial Inputs
            Serial.println("....");
            while (Serial.available() == 0.0) {
            }
            mock = Serial.parseFloat();

        Serial.write("Please Enter Starting Time: \n");
          while (Serial.available() == 0.0) {
            }
          sTime = Serial.parseFloat();
          Serial.write("Starting Time: ");
          Serial.print(sTime);

          
            //Stops skipping the Serial Inputs
            Serial.println("....");
            while (Serial.available() == 0.0) {
            }
            mock = Serial.parseFloat();

        Serial.write("\nPlease Enter Ending Time: \n");
          while (Serial.available() == 0.0) {
            }
          eTime = Serial.parseFloat();
          Serial.write("Ending Time: ");
          Serial.print(eTime);

          FinalTime = (eTime - sTime)/1000;
          Serial.print("\n");
          Serial.write("Final Time: ");
          Serial.print(FinalTime);
          Serial.print("\n");

            //Stops skipping the Serial Inputs
            Serial.println("....");
            while (Serial.available() == 0.0) {
            }
            mock = Serial.parseFloat();
            
        // Implementing d = (Vo)(t) + (0.5)(a)(t)^2
        distance = (0)*(FinalTime)+(0.5)*(FinalAccel)*((FinalTime)*(FinalTime));
        Serial.write("Distance Travelled by Device: ");
        Serial.print(distance);  
        //Radius of arm
        roarm = sqrt((distance)*(distance)/(cos(50)));
        delay(500);
        Serial.print("\n");

            //Stops skipping the Serial Inputs
            Serial.println("....");
            while (Serial.available() == 0.0) {
            }
            mock = Serial.parseFloat();

        //Enter Weight Used
        Serial.println("Please Enter Weight Size Used: ");
        while (Serial.available() == 0) {
          }
        weightSize = Serial.parseFloat();

        
            //Stops skipping the Serial Inputs
            Serial.println("....");
            while (Serial.available() == 0.0) {
            }
            mock = Serial.parseFloat();
  
        trueWeight = weightSize*gravity1;
        force = (trueWeight)*(roarm/100)/(bicepLen);
        work = force*distance/100;
        power = work/FinalTime;
        Serial.print("\n");
        Serial.print("Power of Bicep: ");
        Serial.print(power);
        Serial.print("Nms ");
        Serial.print("\n");
        
        torque = force*sin(50)*bicepLen;
        Serial.print("\n");
        Serial.print("Torque of Bicep: ");
        Serial.print(torque);
        Serial.print("Nms ");
        Serial.print("\n");
          }
        }
 
    else if (ypr[2] * 180 / M_PI > 10) {
    startTime = millis();
    Serial.write("Time: \t");
    Serial.print("\t");
    Serial.println(startTime);
    Serial.write("acceleration: \t");
    Serial.print("\t");
    Serial.print(aaWorld.y);
    Serial.print("\t");
  }
  
  else if (ypr[2] * 180 / M_PI < 10){
    Serial.print("\t");
    Serial.write("Please Preform Muscle Extension:\t");
    Serial.print("\t");   
  }
}

void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
asm volatile ("  jmp 0");  
}  
