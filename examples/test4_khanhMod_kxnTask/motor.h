#include <kxnTask.h>
#include <Makerlabvn_I2C_Motor_Driver.h>

typedef enum MOTOR
{
    MOTOR1,
    MOTOR2,
    MOTOR3,
    MOTOR4,
};

CREATE_TASK(motor)
public:
void setup(MOTOR motor, uint8_t speed, unsigned long timeOut);
void run(bool direction);

private:
uint8_t motorID;
bool direction;
uint8_t speed;
unsigned long timeOut;

Makerlabvn_I2C_Motor_Driver *motorDriver1 = nullptr;
Makerlabvn_I2C_Motor_Driver *motorDriver2 = nullptr;

void init();
void end();

END_CREATE_TASK

void motor::init()
{
    switch (motorID)
    {
    case MOTOR1:
    case MOTOR2:
        if (motorDriver1 == nullptr)
            motorDriver1 = new Makerlabvn_I2C_Motor_Driver(0);
        motorDriver1->begin();
        break;
    case MOTOR3:
    case MOTOR4:
        if (motorDriver2 == nullptr)
            motorDriver2 = new Makerlabvn_I2C_Motor_Driver(1);
        motorDriver2->begin();
        break;
    }
}

void motor::end()
{
    switch (motorID)
    {
    case MOTOR1:
    case MOTOR2:

        delete motorDriver1;
        motorDriver1 = nullptr;
        break;

    case MOTOR3:
    case MOTOR4:

        delete motorDriver2;
        motorDriver2 = nullptr;
        break;
    }
}

void motor::setup(MOTOR motor, uint8_t speed, unsigned long timeOut)
{
    this->motorID = motor;
    this->speed = speed;
    this->timeOut = timeOut;
}

void motor::run(bool direction)
{
    init();
    switch (motorID)
    {
    case MOTOR1:
        motorDriver1->writeMA(direction, speed);
        break;
    case MOTOR2:
        motorDriver1->writeMB(direction, speed);
        break;
    case MOTOR3:
        motorDriver2->writeMA(direction, speed);
        break;
    case MOTOR4:
        motorDriver2->writeMB(direction, speed);
        break;
    }
    end();
}