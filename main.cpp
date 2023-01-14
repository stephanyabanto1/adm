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
    int Servo1Pin = 6;

    error = wiringPiSetupGpio();

    pinMode(Servo1Pin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);

    pwmSetClock(192);
    pwmSetRange(2000);

    if(error != 0) {
        err("error starting wiring pi");
        return 0;
    }

    error = softPwmCreate(Servo1Pin, 50, 100);

    if(error != 0) {
        err("error initializing PWM fn");
        return 0;
    }

    while (true) {
        pwmWrite(Servo1Pin, 50);
        delay(1000);
        pwmWrite(Servo1Pin, 150);
        delay(1000);
        pwmWrite(Servo1Pin, 250);
        delay(1000);
    }  

    return 0;
}