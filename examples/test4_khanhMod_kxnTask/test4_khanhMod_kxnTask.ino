#include "motor.h"
motor myMotor;
motor myMotor2;
#include <Makerlabvn_I2C_Motor_Driver.h>

Makerlabvn_I2C_Motor_Driver myMotor3(0);

void setup() {
  myMotor3.begin();
  // myMotor.setup(MOTOR1, 70, 1000);
  // myMotor2.setup(MOTOR1, 70, 1000);
  // myMotor.run(0);
  // myMotor2.run(0);
  myMotor3.writeMB(0, 70);
  myMotor3.writeMA(0, 70);

  delay(1000);
  myMotor3.writeMB(0, 0);
  myMotor3.writeMA(0, 0);

  // myMotor.stop();
  // myMotor2.stop();
}

void loop() {
  // myMotor.run(1);

  //     myMotor.run(0);
  //     myMotor2.run(1);
  //     delay(1000);
  // kxnTaskManager.run(millis());
}