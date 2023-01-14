#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>

int main()
{
    int Servo1Pin = 1;

    int error = softPwmCreate(Servo1, 50, 100);

    if(error != 0) {
        std::cout << "error initializing PWM fn";
    } else {
        softPwmWrite(Servo1, 5);
    }

    return 0;
}