#pragma once

#include <Makerlabvn_I2C_Motor_Driver.h>
#include <kxnTask.h>

Makerlabvn_I2C_Motor_Driver myDriver(0);
Makerlabvn_I2C_Motor_Driver myDriver2(1);

enum 
// class
CarState {
  MOVE_STRAIGHT,
  MOVE_SIDEWAY,
  MOVE_DIAGONAL,
  MOVE_AROUND,
  ROTATION,
  ROTATION_ARD,
  STOP
};

CREATE_TASK(car_formula)

bool direct = true;
bool side = true;
bool wd = true;

enum Direction {
  LEFT = 0,
  RIGHT = 1
};

enum WheelDirection {
  FORWARD = 1,
  BACKWARD = 0
};

uint8_t speed = 0;
unsigned long delayTime = 0;
CarState runningState = CarState::STOP;

void setup() {
  myDriver.begin();
  myDriver2.begin();
  stop();
}

void loop() {
  switch (getState()) {
    case CarState::MOVE_STRAIGHT:
      myDriver.writeMA(direct, speed);
      myDriver.writeMB(direct, speed);
      myDriver2.writeMA(direct, speed);
      myDriver2.writeMB(direct, speed);
      kDelay(delayTime);
      setState(CarState::STOP);
      break;

    case CarState::MOVE_DIAGONAL:
      if (side == LEFT) {
        if (direct) {
          myDriver.writeMA(direct, speed);
          myDriver2.writeMB(direct, speed);
        } else {
          myDriver.writeMB(direct, speed);
          myDriver2.writeMA(direct, speed);
        }
      } else if (side == RIGHT) {
        if (direct) {
          myDriver.writeMB(direct, speed);
          myDriver2.writeMA(direct, speed);
        } else {
          myDriver.writeMA(direct, speed);
          myDriver2.writeMB(direct, speed);
        }
      }
      kDelay(delayTime);
      setState(CarState::STOP);
      break;

    case CarState::MOVE_SIDEWAY:
      myDriver.writeMA(!direct, speed);
      myDriver.writeMB(direct, speed);
      myDriver2.writeMA(direct, speed);
      myDriver2.writeMB(!direct, speed);
      kDelay(delayTime);
      setState(CarState::STOP);
      break;

    case CarState::MOVE_AROUND:
      if (side == LEFT) {
        myDriver.writeMB(direct, speed);
        myDriver2.writeMB(direct, speed);
      } else if (side == RIGHT) {
        myDriver.writeMA(direct, speed);
        myDriver2.writeMA(direct, speed);
      }
      kDelay(delayTime);
      setState(CarState::STOP);
      break;

    case CarState::ROTATION:
      myDriver.writeMA(!side, speed);
      myDriver.writeMB(side, speed);
      myDriver2.writeMA(!side, speed);
      myDriver2.writeMB(side, speed);
      kDelay(delayTime);
      setState(CarState::STOP);
      break;

    case CarState::ROTATION_ARD:
      if (wd == WheelDirection::FORWARD) {
        myDriver.writeMA(side, speed);
        myDriver.writeMB(!side, speed);
      } else if (wd == WheelDirection::BACKWARD) {
        myDriver2.writeMA(side, speed);
        myDriver2.writeMB(!side, speed);
      }
      kDelay(delayTime);
      setState(CarState::STOP);
      break;

    case CarState::STOP:
      myDriver.writeMA(0, 0);
      myDriver.writeMB(0, 0);
      myDriver2.writeMA(0, 0);
      myDriver2.writeMB(0, 0);
      resetAllPa();
      kDelay(0);
      break;

    default:
      break;
  }
}

void start() {
  kxnTaskManager.add(this);
}

void stop() {
  setState(CarState::STOP);
  kDelay(0);
}

void mov_str(bool direct, uint8_t speed, unsigned long delayTime) {
  if (runningState != CarState::MOVE_STRAIGHT) {
    this->direct = direct;
    this->speed = speed;
    this->delayTime = delayTime;
    runningState = CarState::MOVE_STRAIGHT;
    start();
    setState(CarState::MOVE_STRAIGHT);
  }
}

void mov_sdw(bool direct, uint8_t speed, unsigned long delayTime) {
  if (runningState != CarState::MOVE_SIDEWAY) {
    this->direct = direct;
    this->speed = speed;
    this->delayTime = delayTime;
    runningState = CarState::MOVE_SIDEWAY;
    start();
    setState(CarState::MOVE_SIDEWAY);
  }
}

void mov_dia(bool direct, bool side, uint8_t speed, unsigned long delayTime) {
  if (runningState != CarState::MOVE_DIAGONAL) {
    this->direct = direct;
    this->side = side;
    this->speed = speed;
    this->delayTime = delayTime;
    runningState = CarState::MOVE_DIAGONAL;
    start();
    setState(CarState::MOVE_DIAGONAL);
  }
}

void mov_ard_bd(bool direct, bool side, uint8_t speed, unsigned long delayTime) {
  this->direct = direct;
  this->side = side;
  this->speed = speed;
  this->delayTime = delayTime;
  runningState = CarState::ROTATION_ARD;
  start();
  setState(CarState::MOVE_AROUND);
}

void rotation(bool side, uint8_t speed, unsigned long delayTime) {
  this->side = side;
  this->speed = speed;
  this->delayTime = delayTime;
  runningState = CarState::ROTATION;
  start();
  setState(CarState::ROTATION);
}

void rt_ard_p(bool wd, bool side, uint8_t speed, unsigned long delayTime) {
  this->wd = wd;
  this->side = side;
  this->speed = speed;
  this->delayTime = delayTime;
  runningState = CarState::ROTATION_ARD;
  start();
  setState(CarState::ROTATION_ARD);
}

void stopRunning() {
  resetAllPa();
  setState(CarState::STOP);
  start();
}

bool isRunning() {
  return runningState != CarState::STOP;
}

void resetAllPa() {
  speed = 0;
  delayTime = 0;
  runningState = CarState::STOP;
  direct = true;
  side = true;
  wd = true;
}
END_CREATE_TASK