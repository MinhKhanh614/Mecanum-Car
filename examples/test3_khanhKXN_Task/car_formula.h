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
  STOP
};

CREATE_TASK(car_formula)

bool direct = 1;
bool side = 1;

enum {
  STRAIGHT = 1,
  SIDEWAY,
  DIAGONAL,
  AROUND,
  ROTATION,
  ROTATION_ARD,
  STOP
};

uint8_t speed = 0;
unsigned long delayTime = 0;
uint8_t runningState = 0;
void setup() {
  myDriver.begin();
  myDriver2.begin();
  stop();
}

void loop() {
  switch (getState()) {
    case MOVE_STRAIGHT:
      myDriver.writeMA(this->direct, this->speed);
      myDriver.writeMB(this->direct, this->speed);
      myDriver2.writeMA(this->direct, this->speed);
      myDriver2.writeMB(this->direct, this->speed);
      kDelay(this->delayTime);
      setState(STOP);
      break;

    case MOVE_DIAGONAL:
      switch (this->side) {
        case this->LEFT:
          if (this->direct) {
            myDriver.writeMA(this->direct, this->speed);
            myDriver2.writeMB(this->direct, this->speed);
          } else {
            myDriver.writeMB(this->direct, this->speed);
            myDriver2.writeMA(this->direct, this->speed);
          }
          break;

        case this->RIGHT:
          if (this->direct) {
            myDriver.writeMB(this->direct, this->speed);
            myDriver2.writeMA(this->direct, this->speed);
          } else {
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

void start() {
  kxnTaskManager.add(this);
}

void stop() {
  setState(STOP);
  kDelay(0);
  // setStateIdle();
}

void runFast() {
}

bool forward = 1, backward = 0;

enum {
  LEFT = 0,
  RIGHT = 1
};

typedef enum {
  front = 1,
  back = 0
} car_wd;

void mov_str(bool direct, uint8_t speed, unsigned long delayTime)  // for go straight forward or backward
{
  if (this->runningState != STRAIGHT) {
    // this->stop();
    this->direct = direct;
    this->speed = speed;
    this->delayTime = delayTime;
    this->runningState = STRAIGHT;
    this->start();
    setState(MOVE_STRAIGHT);
  }
}

void mov_sdw(bool direct, uint8_t speed, unsigned long delayTime)  // for go side left or right
{
  if (this->runningState != SIDEWAY) {
    // this->stop();
    this->direct = direct;
    this->speed = speed;
    this->delayTime = delayTime;
    this->runningState = SIDEWAY;
    this->start();
    setState(MOVE_SIDEWAY);
  }
}

void mov_dia(bool direct, bool side, uint8_t pa_speed, unsigned long delayTime)  // for go through to the left or the right
{
  if (this->runningState != DIAGONAL) {
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

void stopRunning() {
  this->resetAllPa();
  setState(STOP);
  this->start();
}

uint8_t isRunning() {
  return this->runningState;
}

void resetAllPa() {
  this->speed = 0;
  this->delayTime = 0;
  this->runningState = 0;
}

END
