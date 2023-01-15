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
    int pin = 18;
    
    /*
    angle must be between:
        50 - 743
    */
    int angle = 50;

    int error = wiringPiSetupGpio();
    if(error != 0) err("wiring pi didn't set up");

    pinMode(pin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);

    pwmSetClock(192);
    pwmSetRange(2000);

    while (true) {
        std::cin >> angle;
        pwmWrite(pin, angle);
    }

    return 0;
}