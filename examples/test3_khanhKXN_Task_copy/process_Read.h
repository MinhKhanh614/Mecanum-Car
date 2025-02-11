#pragma once

#include "kxnTask.h"
#include "read_GamepadModule.h"
#include "car_formula.h"

DEFINE_TASK_STATE(process_Read){};

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
    processMovement();
    processSpecialButtons();

    if (READ1.getPressedButtons() & (1 << READ1.TRIANGLE))
    {
        Serial.println("TRIANGLE");
        digitalWrite(9, HIGH);
    }
    else
    {
        digitalWrite(9, LOW);
    }

    if (READ1.getPressedButtons() & (1 << READ1.CROSS))
    {
        Serial.println("CROSS");
        digitalWrite(10, HIGH);
    }
    else
    {
        digitalWrite(10, LOW);
    }
}

void processMovement()
{
    checkDirection(READ1.UP, READ1.RIGHT, "UP RIGHT", &car_formula::mov_dia, 1, 1, 128, 100);
    checkDirection(READ1.UP, READ1.LEFT, "UP LEFT", &car_formula::mov_dia, 1, 0, 128, 100);
    checkDirection(READ1.DOWN, READ1.RIGHT, "DOWN RIGHT", &car_formula::mov_dia, 0, 1, 128, 100);
    checkDirection(READ1.DOWN, READ1.LEFT, "DOWN LEFT", &car_formula::mov_dia, 0, 0, 128, 100);

    checkSingleButton(READ1.UP, "UP", &car_formula::mov_str, 1, 128, 100);
    checkSingleButton(READ1.DOWN, "DOWN", &car_formula::mov_str, 0, 128, 100);
    checkSingleButton(READ1.LEFT, "LEFT", &car_formula::mov_sdw, 0, 128, 100);
    checkSingleButton(READ1.RIGHT, "RIGHT", &car_formula::mov_sdw, 1, 128, 100);
}

void processSpecialButtons()
{
    if (READ1.getPressedButtons() & (1 << READ1.CIRCLE))
    {
        if (READ1.getPressedButtons() & (1 << READ1.LEFT))
        {
            CAR1.stopRunning();
            CAR1.mov_ard_bd(1, 0, 128, 100);
        }
        else if (READ1.getPressedButtons() & (1 << READ1.RIGHT))
        {
            CAR1.stopRunning();
            CAR1.mov_ard_bd(1, 0, 128, 100);
        }
        else if (READ1.getPressedButtons() & (1 << READ1.DOWN))
        {
            CAR1.stopRunning();
            CAR1.rt_ard_p(0, 1, 128, 100);
        }
        else if (READ1.getPressedButtons() & (1 << READ1.UP))
        {
            CAR1.stopRunning();
            CAR1.rt_ard_p(1, 0, 128, 100);
        }
        else
        {
            CAR1.rotation(1, 128, 10);
            Serial.println("CIRCLE");
        }
    }

    if (READ1.getPressedButtons() & (1 << READ1.SQUARE))
    {
        if (READ1.getPressedButtons() & (1 << READ1.RIGHT))
        {
            CAR1.stopRunning();
            CAR1.mov_ard_bd(1, 1, 128, 100);
        }
        else if (READ1.getPressedButtons() & (1 << READ1.UP))
        {
            CAR1.stopRunning();
            CAR1.rt_ard_p(1, 1, 128, 100);
        }
        else if (READ1.getPressedButtons() & (1 << READ1.LEFT))
        {
            CAR1.stopRunning();
            CAR1.mov_ard_bd(1, 1, 128, 100);
        }
        else if (READ1.getPressedButtons() & (1 << READ1.DOWN))
        {
            CAR1.stopRunning();
            CAR1.rt_ard_p(0, 0, 128, 100);
        }
        else
        {
            Serial.println("SQUARE");
            CAR1.rotation(0, 128, 10);
        }
    }
}

void checkDirection(byte btn1, byte btn2, const char *direction, void (car_formula::*func)(bool, bool, uint8_t, unsigned long), bool arg1, bool arg2, uint8_t arg3, unsigned long arg4)
{
    if ((READ1.getPressedButtons() & (1 << btn1)) && (READ1.getPressedButtons() & (1 << btn2)))
    {
        Serial.println(direction);
        (CAR1.*func)(arg1, arg2, arg3, arg4);
    }
}

void checkSingleButton(byte btn, const char *direction, void (car_formula::*func)(bool, uint8_t, unsigned long), bool arg1, uint8_t arg2, unsigned long arg3)
{
    if (READ1.getPressedButtons() & (1 << btn))
    {
        Serial.println(direction);
        (CAR1.*func)(arg1, arg2, arg3);
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

END_CREATE_TASK
