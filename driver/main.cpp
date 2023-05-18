#include <iostream>
#include "mpu.h"

int main(int argc, char *argv[]){
    float gyro[2];
    
    MPU6050 mpu;

    mpu.calcOffset(false, 0,0);
    mpu.init_MPU();

    while(1) {
        mpu.update();
        mpu.getGyro(gyro);
        printf("%f,%f,%f\r", gyro[0], gyro[1], gyro[2]);
        fflush(stdout);
    }    

    return 0;
}