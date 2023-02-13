#include <wiringPiI2C.h>
#include <wiringPi.h>

#define _USE_MATH_DEFINES
 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <chrono>
#include <cmath>
#include <math.h>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;
auto t0 = Time::now();
auto t1 = Time::now();
fsec fs;

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
int delay_time = 50;



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
	float AccX, AccY, AccZ;
	float GyroX, GyroY, GyroZ;
	float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
	float roll, pitch, yaw;
	float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
	float elapsedTime, currentTime, previousTime;
	int c = 0;

	float Gyro_x,Gyro_y,Gyro_z;
	float Ax=0, Ay=0, Az=0;
	float Gx=0, Gy=0, Gz=0;

    float Dx=0, Dy=0, Dz=0;
    float Px=0, Py=0, Pz=0;
	

	// fd = wiringPiI2CSetup(Device_Address);   /*Initializes I2C with device Address*/
	MPU6050_Init();		                 /* Initializes MPU6050 */
	
	while(1)
	{
		/*Read raw value of Accelerometer and gyroscope from MPU6050*/
		AccX = read_raw_data(ACCEL_XOUT_H)/16384.0;;
		AccY = read_raw_data(ACCEL_YOUT_H)/16384.0;;
		AccZ = read_raw_data(ACCEL_ZOUT_H)/16384.0;;

		accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / M_PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  		accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / M_PI) + 1.58; // 

		previousTime = currentTime;
		t0 = Time::now();
    	t1 = Time::now();

		fs = t1 - t0;

		currentTime = fs.count();
		elapsedTime = (currentTime - previousTime) / 1000; 
		
		GyroX = read_raw_data(GYRO_XOUT_H)/ 131.0;
		GyroY = read_raw_data(GYRO_YOUT_H)/ 131.0;
		GyroZ = read_raw_data(GYRO_ZOUT_H)/ 131.0;

        GyroX = GyroX + 0.56; // GyroErrorX ~(-0.56)
		GyroY = GyroY - 2; // GyroErrorY ~(2)
		GyroZ = GyroZ + 0.79; // GyroErrorZ ~ (-0.8)

		gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
		gyroAngleY = gyroAngleY + GyroY * elapsedTime;
		yaw =  yaw + GyroZ * elapsedTime;

		roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  		pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
		// printf("\n Gx=%.3f °/s\tGy=%.3f °/s\tGz=%.3f °/s\tAx=%.3f g\tAy=%.3f g\tAz=%.3f g\n",Gx,Gy,Gz,Ax,Ay,Az);
		// printf("\n Px=%.3f °\tPy=%.3f °\tPz=%.3f °\n\tAx=%.3f \tAy=%.3f g\tAz=%.3f g\n",Px,Py,Pz,Dx,Dy,Dz);
		printf("%.3f,%.3f,%.3f",yaw,roll,pitch);

		fflush(stdout);
		// delay(delay_time);
	}
	return 0;
}