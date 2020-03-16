#include <SoftwareSerial.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU9250_9Axis_MotionApps41.h"
#include "math.h"

#define INTERRUPT_PIN 2 // use pin 2 on Arduino Uno & most boards

MPU9250 mpu;
// MPU control/status vars
bool dmpReady = false;  
uint8_t mpuIntStatus;   
uint8_t devStatus;      
uint16_t packetSize;    
uint16_t fifoCount;     
uint8_t fifoBuffer[64]; 

Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector


volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}



//여기부터 FSR
SoftwareSerial BTSerial(4, 5); // SoftwareSerial(RX, TX)
byte buffer[256]; // 데이터를 수신 받을 버퍼
int bufferPosition; // 버퍼에 데이타를 저장할 때 기록할 위치
int L_FSR1_Pin = A0; //analog pin 0 엄지
int L_FSR2_Pin = A1; //analog pin 1 엄지밑
int L_FSR3_Pin = A2; //analog pin 2 옆구리
int L_FSR4_Pin = A3; //analog pin 3 뒤꿈치
int L_FSR1 = 0;
int L_FSR2 = 0;
int L_FSR3 = 0;
int L_FSR4 = 0;

void setup(){
  Wire.begin();
  Wire.setClock(400000);
  BTSerial.begin(9600); 
  Serial.begin(9600); 
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);
  //verify connection
  Serial.println(mpu.testConnection() ? "MPU9250 connection successful" : "MPU9250 connection failed");
  // load and configure the DMP
  devStatus = mpu.dmpInitialize();
  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

//   make sure it worked (returns 0 if so)
  if (devStatus == 0) 
  {
     // turn on the DMP, now that it's ready
     Serial.println(F("Enabling DMP..."));
     mpu.setDMPEnabled(true);
     // enable Arduino interrupt detection
     Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
     attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
     mpuIntStatus = mpu.getIntStatus();
     // set our DMP Ready flag so the main loop() function knows it's okay to use it
     Serial.println(F("DMP ready! Waiting for first interrupt..."));
     dmpReady = true;
     // get expected DMP packet size for later comparison
     packetSize = mpu.dmpGetFIFOPacketSize();
  } 
  else 
  {      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      //Serial.print(F("DMP Initialization failed (code "));
      //Serial.print(devStatus);
      //Serial.println(F(")"));
  }

  bufferPosition = 0; // 버퍼 위치 초기화
}

void loop()
{
    // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize);

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();
    
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) 
    {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        //Serial.println(F("FIFO overflow!"));    
    } 
    else if (mpuIntStatus & 0x02) 
    {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    }
  L_FSR1 = analogRead(L_FSR1_Pin);
  L_FSR2 = analogRead(L_FSR2_Pin);
  L_FSR3 = analogRead(L_FSR3_Pin);
  L_FSR4 = analogRead(L_FSR4_Pin);
  
  BTSerial.println(1 + L_FSR1);
  BTSerial.println(1001 + L_FSR2);
  BTSerial.println(2001 + L_FSR3);
  BTSerial.println(3001 + L_FSR4);

  //여기까지 FSR
  int yaw = ypr[0] * 180.0/M_PI;
  int pitch = ypr[1] * 180/M_PI;
  int roll = ypr[2] * 180/M_PI;


//  if(yaw < 0)
//  {
//    yaw = 360 - abs(yaw);
//  }
  

  BTSerial.println(yaw + 7000);
  Serial.print("yaw : ");
  Serial.println(yaw);


    //여기까지 MPU

  //Serial.write(0xff); // Sync byte

  //Serial.write((L_FSR1 >> 8) & 0xff);

  //Serial.write(L_FSR1 & 0xff);
  delay(100);
}
