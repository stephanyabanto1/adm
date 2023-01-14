#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>
#include <string>

void err(std::string str) {
    std::cout << str;
    return;
}

int main()
{
    int error = 0;
    int Servo1Pin = 1;

    error = wiringPiSetup();

    if(error != 0) {
        err("error starting wiring pi");
        return 0;
    }

    error = softPwmCreate(Servo1Pin, 50, 100);

    if(error != 0) {
        err("error initializing PWM fn");
        return 0;
    }

    while( true ) {
        softPwmWrite(Servo1Pin, 5);
    }    
}