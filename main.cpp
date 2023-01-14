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
    int pin = 1;

    printf("Raspberry Pi wiringPi test program\n");
    wiringPiSetupGpio();
    pinMode(pin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);

    pwmSetClock(192);
    pwmSetRange(2000);

    while (true) {
        pwmWrite(pin, 50);
        delay(1000);
        pwmWrite(pin, 150);
        delay(1000);
        pwmWrite(pin, 250);
        delay(1000);
    }

    return 0;
}