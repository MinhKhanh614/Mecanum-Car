#include "MKL_Dabble.h"
#include "car_formula.h"

#define TX_PIN 12
#define RX_PIN 13

void setup_IIC();
void getData();

SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN);
MKE_M15_SSerial(mySoftwareSerial);

void setup_IIC()
{
  mySoftwareSerial.begin(9600);
  Dabble.begin(mySoftwareSerial);
  myDriver.begin();
  myDriver2.begin();
}

void getData()
{
  Dabble.processInput();
}