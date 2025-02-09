#include "motor.h"
motor myMotor;
motor myMotor2;

void setup()
{
    myMotor.setup(MOTOR1, 70, 1000);
    myMotor2.setup(MOTOR2, 70, 1000);
}

void loop()
{
    myMotor.run(1);
    myMotor2.run(0);
    delay(1000);
    myMotor.run(0);
    myMotor2.run(1);
    delay(1000);
}