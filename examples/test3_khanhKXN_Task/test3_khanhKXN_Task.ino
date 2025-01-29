#include "process_Read.h"

process_Read PROCESS;

void setup()
{
PROCESS.setup();
PROCESS.start();
}

void loop()
{
  kxnTaskManager.run(millis());
}