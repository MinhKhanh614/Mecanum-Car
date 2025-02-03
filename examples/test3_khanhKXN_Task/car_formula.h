#pragma once

#include <Makerlabvn_I2C_Motor_Driver.h>
#include "kxnTask.h"

Makerlabvn_I2C_Motor_Driver myDriver(0);
Makerlabvn_I2C_Motor_Driver myDriver2(1);

DEFINE_TASK_STATE(car_formula){
    MOVE_STRAIGHT,
    MOVE_SIDEWAY,
    MOVE_DIAGONAL,
    MOVE_AROUND,
    ROTATION,
    ROTATION_ARD,
    STOP};

CREATE_TASK(car_formula)

bool direct = 1;
bool side = 1;
bool wd;

enum
{
  STRAIGHT = 1,
  SIDEWAY,
  DIAGONAL,
  AROUND,
  ROTATIONS,
  ROTATION_ARD_B,
  ROTATION_ARD_P,
  STOP
};

uint8_t speed = 0;
unsigned long delayTime = 0;
uint8_t runningState = 0;
void setup()
{
  myDriver.begin();
  myDriver2.begin();
  stop();
}

void loop()
{
  switch (getState())
  {
  case MOVE_STRAIGHT:
    myDriver.writeMA(this->direct, this->speed);
    myDriver.writeMB(this->direct, this->speed);
    myDriver2.writeMA(this->direct, this->speed);
    myDriver2.writeMB(this->direct, this->speed);
    kDelay(this->delayTime);
    setState(STOP);
    break;

  case MOVE_DIAGONAL:
    switch (this->side)
    {
    case this->left:
      if (this->direct)
      {
        myDriver.writeMA(this->direct, this->speed);
        myDriver2.writeMB(this->direct, this->speed);
      }
      else
      {
        myDriver.writeMB(this->direct, this->speed);
        myDriver2.writeMA(this->direct, this->speed);
      }
      break;

    case this->right:
      if (this->direct)
      {
        myDriver.writeMB(this->direct, this->speed);
        myDriver2.writeMA(this->direct, this->speed);
      }
      else
      {
        myDriver.writeMA(this->direct, this->speed);
        myDriver2.writeMB(this->direct, this->speed);
      }
      break;

    default:
      break;
    }
    kDelay(this->delayTime);
    setState(STOP);
    break;

  case MOVE_SIDEWAY:
    myDriver.writeMA(!this->direct, this->speed);
    myDriver.writeMB(this->direct, this->speed);
    myDriver2.writeMA(this->direct, this->speed);
    myDriver2.writeMB(!this->direct, this->speed);
    kDelay(this->delayTime);
    setState(STOP);
    break;

  case MOVE_AROUND:
    switch (this->side)
    {
    case this->left:
      myDriver.writeMB(this->direct, this->speed);
      myDriver2.writeMB(this->direct, this->speed);
      break;
    case this->right:
      myDriver.writeMA(this->direct, this->speed);
      myDriver2.writeMA(this->direct, this->speed);
      break;
    default:
      break;
    }
    kDelay(this->delayTime);
    setState(STOP);
    break;

  case ROTATION:
    myDriver.writeMA(!this->side, this->speed);
    myDriver.writeMB(this->side, this->speed);
    myDriver2.writeMA(!this->side, this->speed);
    myDriver2.writeMB(this->side, this->speed);
    kDelay(this->delayTime);
    setState(STOP);
    break;

  case ROTATION_ARD:
    switch (this->wd)
    {
    case this->front:
      myDriver.writeMA(this->side, this->speed);
      myDriver.writeMB(!this->side, this->speed);
      break;

    case this->back:
      myDriver2.writeMA(this->side, this->speed);
      myDriver2.writeMB(!this->side, this->speed);
      break;

    default:
      break;
    }
    kDelay(this->delayTime);
    setState(STOP);
    break;


  case STOP:
    myDriver.writeMA(0, 0);
    myDriver.writeMB(0, 0);
    myDriver2.writeMA(0, 0);
    myDriver2.writeMB(0, 0);
    this->resetAllPa();
    kDelay(0);
    // setStateIdle();
  default:
    break;
  }
}

void start()
{
  kxnTaskManager.add(this);
}

void stop()
{
  setState(STOP);
  kDelay(0);
  // setStateIdle();
}

void runFast()
{
}

bool forward = 1, backward = 0;

enum
{
  left = 0,
  right = 1
};

typedef enum
{
  front = 1,
  back = 0
} car_wd;

void mov_str(bool direct, uint8_t speed, unsigned long delayTime) // for go straight forward or backward
{
  if (this->runningState != STRAIGHT)
  {
    // this->stop();
    this->direct = direct;
    this->speed = speed;
    this->delayTime = delayTime;
    this->runningState = STRAIGHT;
    this->start();
    setState(MOVE_STRAIGHT);
  }
}

void mov_sdw(bool direct, uint8_t speed, unsigned long delayTime) // for go side left or right
{
  if (this->runningState != SIDEWAY)
  {
    // this->stop();
    this->direct = direct;
    this->speed = speed;
    this->delayTime = delayTime;
    this->runningState = SIDEWAY;
    this->start();
    setState(MOVE_SIDEWAY);
  }
}

void mov_dia(bool direct, bool side, uint8_t pa_speed, unsigned long delayTime) // for go through to the left or the right
{
  if (this->runningState != DIAGONAL)
  {
    // this->stop();
    this->direct = direct;
    this->side = side;
    this->speed = pa_speed;
    this->delayTime = delayTime;
    this->runningState = DIAGONAL;
    this->start();
    setState(MOVE_DIAGONAL);
  }
}

void mov_ard_bd(bool direct, bool side, uint8_t pa_speed, unsigned long delayTime) // for go cylce 135 to 225
{
  this->direct = direct;
  this->side = side;
  this->speed = pa_speed;
  this->delayTime = delayTime;
  this->runningState = ROTATION_ARD_B;
  this->start();
  setState(MOVE_AROUND);
}

void rotation(bool side, uint8_t paSpeed, unsigned long delayTime) // rotate by the stand side
{
  this->side = side;
  this->speed = paSpeed;
  this->delayTime = delayTime;
  this->runningState = ROTATIONS;
  this->start();
  setState(ROTATION);
}

void rt_ard_p(bool wd, bool side, uint8_t paSpeed, unsigned long delayTime) // rotate 135 to 45 degree
{
  this->wd = wd;
  this->side = side;
  this->speed = paSpeed;
  this->delayTime = delayTime;
  this->runningState = ROTATION_ARD_P;
  this->start();
  setState(ROTATION_ARD);
}

void stopRunning()
{
  this->resetAllPa();
  setState(STOP);
  this->start();
}

uint8_t isRunning()
{
  return this->runningState;
}

void resetAllPa()
{
  this->speed = 0;
  this->delayTime = 0;
  this->runningState = 0;
  this->direct = 1;
  this->side = 1;
  this->wd = 1;
}

END
