#include <wiringPiI2C.h>
#include <wiringPi.h>

#define _USE_MATH_DEFINES
 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <chrono>
#include <cmath>
#include <math.h>


// using namespace std::chrono;

// milliseconds ms = duration_cast< milliseconds >(
//     system_clock::now().time_since_epoch()
// );

#define Device_Address 0x68	/*Device Address/Identifier for MPU6050*/

#define PWR_MGMT_1   0x6B
#define SMPLRT_DIV   0x19
#define CONFIG       0x1A
#define GYRO_CONFIG  0x1B
#define INT_ENABLE   0x38
#define ACCEL_XOUT_H 0x3B
#define ACCEL_YOUT_H 0x3D
#define ACCEL_ZOUT_H 0x3F
#define GYRO_XOUT_H  0x43
#define GYRO_YOUT_H  0x45
#define GYRO_ZOUT_H  0x47


int fd;

void MPU6050_Init(){
	
	wiringPiI2CWriteReg8 (fd, SMPLRT_DIV, 0x07);	/* Write to sample rate register */
	wiringPiI2CWriteReg8 (fd, PWR_MGMT_1, 0x01);	/* Write to power management register */
	wiringPiI2CWriteReg8 (fd, CONFIG, 0);		/* Write to Configuration register */
	wiringPiI2CWriteReg8 (fd, GYRO_CONFIG, 24);	/* Write to Gyro Configuration register */
	wiringPiI2CWriteReg8 (fd, INT_ENABLE, 0x01);	/*Write to interrupt enable register */

} 

short read_raw_data(int addr){
	short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(fd, addr);
	low_byte = wiringPiI2CReadReg8(fd, addr+1);
	value = (high_byte << 8) | low_byte;
	return value;
}

void ms_delay(int val){
	int i,j;
	for(i=0;i<=val;i++)
		for(j=0;j<1200;j++);
}

int main(){
	int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;
	float Acceleration_angle[3];
	float Gyro_angle[3];
	float Total_angle[3];
	float elapsedTime, time, timePrev;
	int i;
	float rad_to_deg = 180/3.141592654;


	fd = wiringPiI2CSetup(Device_Address);   /*Initializes I2C with device Address*/
	MPU6050_Init();		                 /* Initializes MPU6050 */
	
	while(1)
	{
		timePrev = time;  // the previous time is stored before the actual time read
		time = ms.count();  // actual time read
		elapsedTime = (time - timePrev) / 1000;
		///16384.0
		Acc_rawX = read_raw_data(ACCEL_XOUT_H)/16384.0;
		Acc_rawY = read_raw_data(ACCEL_YOUT_H)/16384.0;
		Acc_rawZ = read_raw_data(ACCEL_ZOUT_H)/16384.0;
		
		/*---X---*/
		Acceleration_angle[0] = atan((Acc_rawY)/sqrt(pow((Acc_rawX),2) + pow((Acc_rawZ),2)))*rad_to_deg;
		/*---Y---*/
		Acceleration_angle[1] = atan(-1*(Acc_rawX)/sqrt(pow((Acc_rawY),2) + pow((Acc_rawZ),2)))*rad_to_deg;
		
		Acceleration_angle[2] = atan(sqrt(Acc_rawX*Acc_rawX + Acc_rawY*Acc_rawY)/Acc_rawZ) *rad_to_deg;
	
		Gyr_rawX = read_raw_data(GYRO_XOUT_H);
		Gyr_rawY = read_raw_data(GYRO_YOUT_H);
		Gyr_rawZ = read_raw_data(GYRO_ZOUT_H);

		/*---X---*/
		Gyro_angle[0] = Gyr_rawX/131.0; 
		/*---Y---*/
		Gyro_angle[1] = Gyr_rawY/131.0;
    Gyro_angle[2] = Gyr_rawZ/131.0;


		/*---X axis angle---*/
		Total_angle[0] = 0.98 *(Total_angle[0] + Gyro_angle[0]*elapsedTime) + 0.02*Acceleration_angle[0];
		/*---Y axis angle---*/
		Total_angle[1] = 0.98 *(Total_angle[1] + Gyro_angle[1]*elapsedTime) + 0.02*Acceleration_angle[1];
		
		Total_angle[2] = Total_angle[2] + Gyro_angle[2]*elapsedTime;

		printf("%f,%f,%f\r", Total_angle[0], Total_angle[1], Total_angle[2]);

		fflush(stdout);
	}
	return 0;
}



MPU6050::MPU6050(TwoWire &w){
  wire = &w;
  accCoef = 0.02f;
  gyroCoef = 0.98f;
}

MPU6050::MPU6050(TwoWire &w, float aC, float gC){
  wire = &w;
  accCoef = aC;
  gyroCoef = gC;
}

void MPU6050::begin(){
  writeMPU6050(MPU6050_SMPLRT_DIV, 0x00);
  writeMPU6050(MPU6050_CONFIG, 0x00);
  writeMPU6050(MPU6050_GYRO_CONFIG, 0x08);
  writeMPU6050(MPU6050_ACCEL_CONFIG, 0x00);
  writeMPU6050(MPU6050_PWR_MGMT_1, 0x01);
  this->update();
  angleGyroX = 0;
  angleGyroY = 0;
  angleX = this->getAccAngleX();
  angleY = this->getAccAngleY();
  preInterval = millis();
}

void MPU6050::writeMPU6050(byte reg, byte data){
  wire->beginTransmission(MPU6050_ADDR);
  wire->write(reg);
  wire->write(data);
  wire->endTransmission();
}

byte MPU6050::readMPU6050(byte reg) {
  wire->beginTransmission(MPU6050_ADDR);
  wire->write(reg);
  wire->endTransmission(true);
  wire->requestFrom(MPU6050_ADDR, 1);
  byte data =  wire->read();
  return data;
}

void MPU6050::setGyroOffsets(float x, float y, float z){
  gyroXoffset = x;
  gyroYoffset = y;
  gyroZoffset = z;
}

void MPU6050::calcGyroOffsets(bool console, uint16_t delayBefore, uint16_t delayAfter){
	float x = 0, y = 0, z = 0;
	int16_t rx, ry, rz;

  delay(delayBefore);
	if(console){
    Serial.println();
    Serial.println("========================================");
    Serial.println("Calculating gyro offsets");
    Serial.print("DO NOT MOVE MPU6050");
  }
  for(int i = 0; i < 3000; i++){
    if(console && i % 1000 == 0){
      Serial.print(".");
    }
    wire->beginTransmission(MPU6050_ADDR);
    wire->write(0x43);
    wire->endTransmission(false);
    wire->requestFrom((int)MPU6050_ADDR, 6);

    rx = wire->read() << 8 | wire->read();
    ry = wire->read() << 8 | wire->read();
    rz = wire->read() << 8 | wire->read();

    x += ((float)rx) / 65.5;
    y += ((float)ry) / 65.5;
    z += ((float)rz) / 65.5;
  }
  gyroXoffset = x / 3000;
  gyroYoffset = y / 3000;
  gyroZoffset = z / 3000;

  if(console){
    Serial.println();
    Serial.println("Done!");
    Serial.print("X : ");Serial.println(gyroXoffset);
    Serial.print("Y : ");Serial.println(gyroYoffset);
    Serial.print("Z : ");Serial.println(gyroZoffset);
    Serial.println("Program will start after 3 seconds");
    Serial.print("========================================");
		delay(delayAfter);
	}
}

void MPU6050::update(){
	wire->beginTransmission(MPU6050_ADDR);
	wire->write(0x3B);
	wire->endTransmission(false);
	wire->requestFrom((int)MPU6050_ADDR, 14);

  rawAccX = wire->read() << 8 | wire->read();
  rawAccY = wire->read() << 8 | wire->read();
  rawAccZ = wire->read() << 8 | wire->read();
  rawTemp = wire->read() << 8 | wire->read();
  rawGyroX = wire->read() << 8 | wire->read();
  rawGyroY = wire->read() << 8 | wire->read();
  rawGyroZ = wire->read() << 8 | wire->read();

  temp = (rawTemp + 12412.0) / 340.0;

  accX = ((float)rawAccX) / 16384.0;
  accY = ((float)rawAccY) / 16384.0;
  accZ = ((float)rawAccZ) / 16384.0;

  angleAccX = atan2(accY, sqrt(accZ * accZ + accX * accX)) * 360 / 2.0 / PI;
  angleAccY = atan2(accX, sqrt(accZ * accZ + accY * accY)) * 360 / -2.0 / PI;

  gyroX = ((float)rawGyroX) / 65.5;
  gyroY = ((float)rawGyroY) / 65.5;
  gyroZ = ((float)rawGyroZ) / 65.5;

  gyroX -= gyroXoffset;
  gyroY -= gyroYoffset;
  gyroZ -= gyroZoffset;

  interval = (millis() - preInterval) * 0.001;

  angleGyroX += gyroX * interval;
  angleGyroY += gyroY * interval;
  angleGyroZ += gyroZ * interval;

  angleX = (gyroCoef * (angleX + gyroX * interval)) + (accCoef * angleAccX);
  angleY = (gyroCoef * (angleY + gyroY * interval)) + (accCoef * angleAccY);
  angleZ = angleGyroZ;

  preInterval = millis();

}