#include "mecanumCar.h"
#include <kxnTask.h>
mecanumCar CAR;

void setup() {
  CAR.setup();
  CAR.start();
  // Serial.begin(115200);
}

void loop() {
  kxnTaskManager.run(millis());
  // Serial.println("Test");
  }
