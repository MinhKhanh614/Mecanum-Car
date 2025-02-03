#pragma once

#include "kxnTask.h"
#include "MKL_Dabble.h"

#define TX_PIN 12
#define RX_PIN 13

// #define KDEBUG

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN);
MKE_M15_SSerial(mySoftwareSerial);

DEFINE_TASK_STATE(read_GamepadModule){

};

CREATE_TASK(read_GamepadModule)

enum LEFT_GAMEPAD
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

// enum MID_GAMEPAD
// {
//     SELECT,
//     START
// };

enum RIGHT_GAMEPAD
{
    CIRCLE = 4,
    SQUARE,
    TRIANGLE,
    CROSS
};
// byte value;
byte pressedButtons = 0;


void setup()
{
    mySoftwareSerial.begin(9600);
    Dabble.begin(mySoftwareSerial);

    #ifdef KDEBUG
    Serial.begin(115200);
    Serial.println("Setup Complete");
    #endif

    stop();
}

void loop()
{

    #ifdef KDEBUG
    Serial.print(GamePad.isUpPressed());
    Serial.print(" ");
    Serial.print(GamePad.isDownPressed());
    Serial.print(" ");
    Serial.print(GamePad.isLeftPressed());
    Serial.print(" ");
    Serial.print(GamePad.isRightPressed());
    Serial.print(" ");
    Serial.print(GamePad.isStartPressed());
    Serial.print(" ");
    Serial.print(GamePad.isSelectPressed());
    Serial.print(" ");
    Serial.print(GamePad.isTrianglePressed());
    Serial.print(" ");
    Serial.print(GamePad.isCirclePressed());
    Serial.print(" ");
    Serial.print(GamePad.isCrossPressed());
    Serial.print(" ");
    Serial.print(GamePad.isSquarePressed());
    Serial.println();
    #endif

    if (GamePad.isUpPressed())
    {
        this->pressedButtons |= (1 << this->UP);
    }
    else
    {
        this->pressedButtons &= ~(1 << this->UP);
    }

    if (GamePad.isDownPressed())
    {
        this->pressedButtons |= (1 << this->DOWN);
    }
    else
    {
        this->pressedButtons &= ~(1 << this->DOWN);
    }

    if (GamePad.isLeftPressed())
    {
        this->pressedButtons |= (1 << this->LEFT);
    }
    else
    {
        this->pressedButtons &= ~(1 << this->LEFT);
    }

    if (GamePad.isRightPressed())
    {
        this->pressedButtons |= (1 << this->RIGHT);
    }
    else
    {
        this->pressedButtons &= ~(1 << this->RIGHT);
    }
    
    if (GamePad.isTrianglePressed())
    {
        this->pressedButtons |= (1 << this->TRIANGLE);
    }
    else
    {
        this->pressedButtons &= ~(1 << this->TRIANGLE);
    }

    if (GamePad.isCirclePressed())
    {
        this->pressedButtons |= (1 << this->CIRCLE);
    }
    else
    {
        this->pressedButtons &= ~(1 << this->CIRCLE);
    }

    if (GamePad.isCrossPressed())
    {
        this->pressedButtons |= (1 << this->CROSS);
    }
    else
    {
        this->pressedButtons &= ~(1 << this->CROSS);
    }

    if (GamePad.isSquarePressed())
    {
        this->pressedButtons |= (1 << this->SQUARE);
    }
    else
    {
        this->pressedButtons &= ~(1 << this->SQUARE);
    }
    
    
    // if (GamePad.isPressed(1)==0) this->pressedButtons = 0;

}

void start()
{
    setState(0);
    kxnTaskManager.add(this);
}

void stop()
{
    kDelay(0);
    setStateIdle();
}

byte getPressedButtons()
{
    // this->pressedButtons = 0;
    // kxnTaskManager.add(this);
    // setState(0);
    return this->pressedButtons;
}

void runFast()
{
    Dabble.processInput();
}

END
