#pragma once

#include "kxnTask.h"
#include "read_GamepadModule.h"
#include "car_formula.h"

DEFINE_TASK_STATE(process_Read){

};

CREATE_TASK(process_Read)

read_GamepadModule READ1;
car_formula CAR1;

void setup()
{
  READ1.setup();
  READ1.start();
  CAR1.setup();
  Serial.begin(115200);
  this->stop();
}

void loop()
{
  // Serial.println(CAR1.runningState);
  if (READ1.getPressedButtons() & (1 << READ1.UP))
  {
    if (READ1.getPressedButtons() & (1 << READ1.UP) && READ1.getPressedButtons() & (1 << READ1.RIGHT))
    {
      // CAR1.stopRunning();
      Serial.println("UP RIGHT");
      CAR1.mov_dia(1, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.UP) && READ1.getPressedButtons() & (1 << READ1.SQUARE))
    {
      // CAR1.stopRunning();
      // Serial.println("UP RIGHT");
      // CAR1.mov_ard_bd(1, 0, 128, 100);
      CAR1.stopRunning();
      CAR1.rt_ard_p(1, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.UP) && READ1.getPressedButtons() & (1 << READ1.CIRCLE))
    {
      // CAR1.stopRunning();
      // Serial.println("UP RIGHT");
      // CAR1.mov_ard_bd(1, 0, 128, 100);
      CAR1.stopRunning();
      CAR1.rt_ard_p(1, 0, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.UP) && READ1.getPressedButtons() & (1 << READ1.LEFT))
    {
      // CAR1.stopRunning();
      // Serial.println("UP LEFT");
      CAR1.mov_dia(1, 0, 128, 100);
    }
    else
    {
      // CAR1.stopRunning();
      Serial.println("UP");
      CAR1.mov_str(1, 128, 100);
    }
  }

  if (READ1.getPressedButtons() & (1 << READ1.DOWN))
  {
    if (READ1.getPressedButtons() & (1 << READ1.DOWN) && READ1.getPressedButtons() & (1 << READ1.RIGHT))
    {
      // CAR1.stopRunning();
      Serial.println("DOWN RIGHT");
      CAR1.mov_dia(0, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.DOWN) && READ1.getPressedButtons() & (1 << READ1.SQUARE))
    {
      // CAR1.stopRunning();
      // Serial.println("UP RIGHT");
      // CAR1.mov_ard_bd(1, 0, 128, 100);
      CAR1.stopRunning();
      CAR1.rt_ard_p(0, 0, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.DOWN) && READ1.getPressedButtons() & (1 << READ1.CIRCLE))
    {
      // CAR1.stopRunning();
      // Serial.println("UP RIGHT");
      // CAR1.mov_ard_bd(1, 0, 128, 100);
      CAR1.stopRunning();
      CAR1.rt_ard_p(0, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.DOWN) && READ1.getPressedButtons() & (1 << READ1.LEFT))
    {
      // CAR1.stopRunning();
      Serial.println("DOWN LEFT");
      CAR1.mov_dia(0, 0, 128, 100);
    }
    else
    {
      // CAR1.stopRunning();
      Serial.println("DOWN");
      CAR1.mov_str(0, 128, 100);
    }
  }

  if (READ1.getPressedButtons() & (1 << READ1.LEFT))
  {
    if (READ1.getPressedButtons() & (1 << READ1.UP) && READ1.getPressedButtons() & (1 << READ1.LEFT))
    {
      // CAR1.stopRunning();
      Serial.println("UP LEFT");
      CAR1.mov_dia(1, 0, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.LEFT) && READ1.getPressedButtons() & (1 << READ1.SQUARE))
    {
      // CAR1.stopRunning();
      // Serial.println("UP RIGHT");
      // CAR1.mov_ard_bd(1, 0, 128, 100);
      CAR1.stopRunning();
      CAR1.mov_ard_bd(1, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.LEFT) && READ1.getPressedButtons() & (1 << READ1.CIRCLE))
    {
      // CAR1.stopRunning();
      // Serial.println("UP RIGHT");
      // CAR1.mov_ard_bd(1, 0, 128, 100);
      CAR1.stopRunning();
      CAR1.mov_ard_bd(1, 0, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.DOWN) && READ1.getPressedButtons() & (1 << READ1.LEFT))
    {
      // CAR1.stopRunning();
      Serial.println("DOWN LEFT");
      CAR1.mov_dia(0, 0, 128, 100);
    }
    else
    {
      // CAR1.stopRunning();
      Serial.println("LEFT");
      CAR1.mov_sdw(0, 128, 100);
    }
    Serial.println("LEFT");
  }

  if (READ1.getPressedButtons() & (1 << READ1.RIGHT))
  {
    if (READ1.getPressedButtons() & (1 << READ1.UP) && READ1.getPressedButtons() & (1 << READ1.RIGHT))
    {
      // CAR1.stopRunning();
      Serial.println("UP RIGHT");
      CAR1.mov_dia(1, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.DOWN) && READ1.getPressedButtons() & (1 << READ1.RIGHT))
    {
      // CAR1.stopRunning();
      Serial.println("DOWN RIGHT");
      CAR1.mov_dia(0, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.RIGHT) && READ1.getPressedButtons() & (1 << READ1.SQUARE))
    {
      CAR1.stopRunning();
      CAR1.mov_ard_bd(1, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.RIGHT) && READ1.getPressedButtons() & (1 << READ1.CIRCLE))
    {
      CAR1.stopRunning();
      CAR1.mov_ard_bd(1, 0, 128, 100);
    }
    else
    {
      Serial.println("RIGHT");
      CAR1.mov_sdw(1, 128, 100);
    }
  }
  if (READ1.getPressedButtons() & (1 << READ1.TRIANGLE))
  {
    // CAR1.stopRunning();
    Serial.println("TRIANGLE");
    // CAR1.mov_str(1, 128, 100);
    digitalWrite(9, HIGH);
  }
  else
  {
    digitalWrite(9, LOW);
  }

  if (
      // !READ1.getPressedButtons() & (1 << READ1.UP) &&
      // !READ1.getPressedButtons() & (1 << READ1.DOWN) &&
      // !READ1.getPressedButtons() & (1 << READ1.LEFT) &&
      // !READ1.getPressedButtons() & (1 << READ1.RIGHT) &&
      READ1.getPressedButtons() & (1 << READ1.CIRCLE))
  {
    if (READ1.getPressedButtons() & (1 << READ1.LEFT) && READ1.getPressedButtons() & (1 << READ1.CIRCLE))
    {
      // CAR1.stopRunning();
      // Serial.println("UP RIGHT");
      // CAR1.mov_ard_bd(1, 0, 128, 100);
      CAR1.stopRunning();
      CAR1.mov_ard_bd(1, 0, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.RIGHT) && READ1.getPressedButtons() & (1 << READ1.CIRCLE))
    {
      CAR1.stopRunning();
      CAR1.mov_ard_bd(1, 0, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.DOWN) && READ1.getPressedButtons() & (1 << READ1.CIRCLE))
    {
      CAR1.stopRunning();
      CAR1.rt_ard_p(0, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.UP) && READ1.getPressedButtons() & (1 << READ1.CIRCLE))
    {
      CAR1.stopRunning();
      CAR1.rt_ard_p(1, 0, 128, 100);
    }
    else
    {
      // CAR1.stopRunning();
      CAR1.rotation(1, 128, 10);
      Serial.println("CIRCLE");
    }
  }

  if (READ1.getPressedButtons() & (1 << READ1.CROSS))
  {
    // CAR1.stopRunning();
    Serial.println("CROSS");
    digitalWrite(10, HIGH);
  }
  else
  {
    digitalWrite(10, LOW);
  }

  if (
      // !READ1.getPressedButtons() & (1 << READ1.UP) &&
      // !READ1.getPressedButtons() & (1 << READ1.DOWN) &&
      // !READ1.getPressedButtons() & (1 << READ1.LEFT) &&
      // !READ1.getPressedButtons() & (1 << READ1.RIGHT) &&
      READ1.getPressedButtons() & (1 << READ1.SQUARE))
  {
    if (READ1.getPressedButtons() & (1 << READ1.RIGHT) && READ1.getPressedButtons() & (1 << READ1.SQUARE))
    {
      CAR1.stopRunning();
      CAR1.mov_ard_bd(1, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.UP) && READ1.getPressedButtons() & (1 << READ1.SQUARE))
    {
      CAR1.stopRunning();
      CAR1.rt_ard_p(1, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.LEFT) && READ1.getPressedButtons() & (1 << READ1.SQUARE))
    {
      CAR1.stopRunning();
      CAR1.mov_ard_bd(1, 1, 128, 100);
    }
    else if (READ1.getPressedButtons() & (1 << READ1.DOWN) && READ1.getPressedButtons() & (1 << READ1.SQUARE))
    {
      CAR1.stopRunning();
      CAR1.rt_ard_p(0, 0, 128, 100);
    }
    else
    {
      // CAR1.stopRunning();
      Serial.println("SQUARE");
      CAR1.rotation(0, 128, 10);
      // CAR1.mov_ard_bd(1, 0, 128, 100);
      // CAR1.rt_ard_p(1, 0, 128, 100);
      // CAR1.mov_str(1, 128, 100);
      // digitalWrite(12, HIGH);
    }
  }
}

void start()
{
  kxnTaskManager.add(this);
  setState(0);
}

void stop()
{
  kDelay(0);
  setStateIdle();
}

void runFast()
{
}

END
