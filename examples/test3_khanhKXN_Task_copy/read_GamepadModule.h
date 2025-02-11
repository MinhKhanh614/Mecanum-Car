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

typedef void*(myFuntion)();

CREATE_TASK(read_GamepadModule)
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

enum BUTTON {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    TRIANGLE,
    CIRCLE,
    CROSS,
    SQUARE,
    BUTTON_COUNT
};

void checkButtonState(GamePadModule &GamePad) {
    bool(GamePadModule::*buttonFuncs[BUTTON_COUNT])() = {
        &GamePadModule::isUpPressed,
        &GamePadModule::isDownPressed,
        &GamePadModule::isLeftPressed,
        &GamePadModule::isRightPressed,
        &GamePadModule::isTrianglePressed,
        &GamePadModule::isCirclePressed,
        &GamePadModule::isCrossPressed,
        &GamePadModule::isSquarePressed
    };

    for (int i = 0; i < BUTTON_COUNT; ++i) {
        if ((GamePad.*buttonFuncs[i])())
            pressedButtons |= (1 << i);
        else
            pressedButtons &= ~(1 << i);
    }
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

    checkButtonState(GamePad);
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
    return this->pressedButtons;
}

void runFast()
{
    Dabble.processInput();
}

END_CREATE_TASK




