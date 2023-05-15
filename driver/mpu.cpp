#include "mpu.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <cmath>
#include <math.h>


MPU6050::MPU6050 (int fd){
	//check if fd is successfull connect
	MPU6050::fd = fd;
}

short MPU6050::read_raw_data(int addr){
	short high_byte,low_byte,value;
	high_byte = wiringPiI2CReadReg8(MPU6050::fd, addr);
	low_byte = wiringPiI2CReadReg8(MPU6050::fd, addr+1);
	value = (high_byte << 8) | low_byte;
	return value;
}

void MPU6050::calcOffset(bool console, uint16_t delayBefore, uint16_t delayAfter) {
    float x = 0, y = 0, z = 0;
	int16_t rx, ry, rz;

    delay(delayBefore);
    if(console){
        std::cout << "Calculating gyro offsets" << std::endl;
    }
  for(int i = 0; i < 3000; i++){
    if(console && i % 1000 == 0){
      printf(".");
    }
    
    // wiringPiI2CWriteReg8 (fd, SMPLRT_DIV, 0x43);
    // wire->beginTransmission(MPU6050_ADDR);
    // wire->write(0x43);
    // wire->endTransmission(false);
    // wire->requestFrom((int)MPU6050_ADDR, 6);

    rx = read_raw_data(GYRO_XOUT_H);
    ry = read_raw_data(GYRO_YOUT_H);
    rz = read_raw_data(GYRO_ZOUT_H);

    x += ((float)rx) / 65.5;
    y += ((float)ry) / 65.5;
    z += ((float)rz) / 65.5;
  }
  gyroXoffset = x / 3000;
  gyroYoffset = y / 3000;
  gyroZoffset = z / 3000;

  if(console){
	  std::cout << "Calculating gyro offsets" << std::endl;
	  std::cout << "X: " << gyroXoffset << std::endl;
	  std::cout << "Y: " << gyroXoffset << std::endl;
	  std::cout << "Z: " << gyroXoffset << std::endl;
	delay(delayAfter);
	}
}