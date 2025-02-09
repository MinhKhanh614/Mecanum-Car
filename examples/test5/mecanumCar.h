#pragma once
#include <kxnTask.h>
#include "car_formula.h"
#include <MKL_Dabble.h>

#define TX_PIN 12
#define RX_PIN 13

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN);
MKE_M15_SSerial(mySoftwareSerial);
car_formula CAR1;

CREATE_TASK(mecanumCar)

void setup()
{
    Dabble.begin(mySoftwareSerial);
    mySoftwareSerial.begin(9600);
    CAR1.setup();
}


void loop() {
    printButtonStates();

    if (GamePad.isUpPressed()) {
        handleUpButton();
    } else if (GamePad.isDownPressed()) {
        handleDownButton();
    } else if (GamePad.isLeftPressed()) {
        handleLeftButton();
    } else if (GamePad.isRightPressed()) {
        handleRightButton();
    }

    handleSpecialButtons();
}

void printButtonStates() {
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
}

void handleUpButton() {
    if (GamePad.isRightPressed()) {
        Serial.println("UP RIGHT");
        CAR1.mov_dia(true, true, 128, 100);
    } else if (GamePad.isSquarePressed()) {
        CAR1.stopRunning();
        CAR1.rt_ard_p(true, true, 128, 100);
    } else if (GamePad.isCirclePressed()) {
        CAR1.stopRunning();
        CAR1.rt_ard_p(true, false, 128, 100);
    } else if (GamePad.isLeftPressed()) {
        Serial.println("UP LEFT");
        CAR1.mov_dia(true, false, 128, 100);
    } else {
        Serial.println("UP");
        CAR1.mov_str(true, 128, 100);
    }
}

void handleDownButton() {
    if (GamePad.isRightPressed()) {
        Serial.println("DOWN RIGHT");
        CAR1.mov_dia(false, true, 128, 100);
    } else if (GamePad.isSquarePressed()) {
        CAR1.stopRunning();
        CAR1.rt_ard_p(false, false, 128, 100);
    } else if (GamePad.isCirclePressed()) {
        CAR1.stopRunning();
        CAR1.rt_ard_p(false, true, 128, 100);
    } else if (GamePad.isLeftPressed()) {
        Serial.println("DOWN LEFT");
        CAR1.mov_dia(false, false, 128, 100);
    } else {
        Serial.println("DOWN");
        CAR1.mov_str(false, 128, 100);
    }
}

void handleLeftButton() {
    if (GamePad.isUpPressed()) {
        Serial.println("UP LEFT");
        CAR1.mov_dia(true, false, 128, 100);
    } else if (GamePad.isSquarePressed()) {
        CAR1.stopRunning();
        CAR1.mov_ard_bd(true, true, 128, 100);
    } else if (GamePad.isCirclePressed()) {
        CAR1.stopRunning();
        CAR1.mov_ard_bd(true, false, 128, 100);
    } else if (GamePad.isDownPressed()) {
        Serial.println("DOWN LEFT");
        CAR1.mov_dia(false, false, 128, 100);
    } else {
        Serial.println("LEFT");
        CAR1.mov_sdw(false, 128, 100);
    }
}

void handleRightButton() {
    if (GamePad.isUpPressed()) {
        Serial.println("UP RIGHT");
        CAR1.mov_dia(true, true, 128, 100);
    } else if (GamePad.isDownPressed()) {
        Serial.println("DOWN RIGHT");
        CAR1.mov_dia(false, true, 128, 100);
    } else if (GamePad.isSquarePressed()) {
        CAR1.stopRunning();
        CAR1.mov_ard_bd(true, true, 128, 100);
    } else if (GamePad.isCirclePressed()) {
        CAR1.stopRunning();
        CAR1.mov_ard_bd(true, false, 128, 100);
    } else {
        Serial.println("RIGHT");
        CAR1.mov_sdw(true, 128, 100);
    }
}

void handleSpecialButtons() {
    if (GamePad.isTrianglePressed()) {
        Serial.println("TRIANGLE");
        digitalWrite(9, HIGH);
    } else {
        digitalWrite(9, LOW);
    }

    if (GamePad.isCirclePressed()) {
        handleCircleButton();
    } else if (GamePad.isCrossPressed()) {
        Serial.println("CROSS");
        digitalWrite(10, HIGH);
    } else {
        digitalWrite(10, LOW);
    }

    if (GamePad.isSquarePressed()) {
        handleSquareButton();
    }
}

void handleCircleButton() {
    if (GamePad.isLeftPressed()) {
        CAR1.stopRunning();
        CAR1.mov_ard_bd(true, false, 128, 100);
    } else if (GamePad.isRightPressed()) {
        CAR1.stopRunning();
        CAR1.mov_ard_bd(true, false, 128, 100);
    } else if (GamePad.isDownPressed()) {
        CAR1.stopRunning();
        CAR1.rt_ard_p(false, true, 128, 100);
    } else if (GamePad.isUpPressed()) {
        CAR1.stopRunning();
        CAR1.rt_ard_p(true, false, 128, 100);
    } else {
        CAR1.rotation(true, 128, 10);
        Serial.println("CIRCLE");
    }
}

void handleSquareButton() {
    if (GamePad.isRightPressed()) {
        CAR1.stopRunning();
        CAR1.mov_ard_bd(true, true, 128, 100);
    } else if (GamePad.isUpPressed()) {
        CAR1.stopRunning();
        CAR1.rt_ard_p(true, true, 128, 100);
    } else if (GamePad.isLeftPressed()) {
        CAR1.stopRunning();
        CAR1.mov_ard_bd(true, true, 128, 100);
    } else if (GamePad.isDownPressed()) {
        CAR1.stopRunning();
        CAR1.rt_ard_p(false, false, 128, 100);
    } else {
        Serial.println("SQUARE");
        CAR1.rotation(false, 128, 10);
    }
}

void start() {
    kxnTaskManager.add(this);
    setState(0);
}

void stop() {
    kDelay(0);
    setStateIdle();
}

void runFast()
{
    Dabble.processInput();
}

END_CREATE_TASK



