#include <SPI.h>
#include <HighPowerStepperDriver.h>

const uint8_t CSPin2 = 10;
const uint8_t CSPin = 9;
// This period is the length of the delay between steps, which controls the
// stepper motor's speed.  You can increase the delay to make the stepper motor
// go slower.  If you decrease the delay, the stepper motor will go faster, but
// there is a limit to how fast it can go before it starts missing steps.
const uint16_t StepPeriodUs = 2000;

HighPowerStepperDriver sd;
HighPowerStepperDriver sd2;

void setup()
{
  SPI.begin();
  sd.setChipSelectPin(CSPin);
  sd2.setChipSelectPin(CSPin2);
  //sd.setChipSelectPin(CSPin1);
  // Give the driver some time to power up.
  delay(2);

  // Reset the driver to its default settings and clear latched status
  // conditions.
  sd.resetSettings();
  sd.clearStatus();
  sd2.resetSettings();
  sd2.clearStatus();

  // Select auto mixed decay.  TI's DRV8711 documentation recommends this mode
  // for most applications, and we find that it usually works well.
  //sd.setDecayMode(HPSDDecayMode::AutoMixed);

  // Set the current limit. You should change the number here to an appropriate
  // value for your particular system.
  sd.setCurrentMilliamps36v4(2800);//(mA)per coil / 8A max
  sd2.setCurrentMilliamps36v4(2800);//(mA)per coil / 8A max

  // Set the number of microsteps that correspond to one full step.
  sd.setStepMode(HPSDStepMode::MicroStep1);
  sd2.setStepMode(HPSDStepMode::MicroStep1);

  // Enable the motor outputs.
  sd.enableDriver();
  sd2.enableDriver();

  //pinMode(49, OUTPUT);
  //digitalWrite(49, HIGH);
}

void loop()
{
  // Step in the default direction 1000 times.
  sd.setDirection(0);//cc
  sd2.setDirection(0);//cc
  //delayMicroseconds(100);
  for(unsigned int x = 0; x < 1000; x++)
  {
    sd.step();
    sd2.step();
    delayMicroseconds(StepPeriodUs);
  }

  // Wait for 300 ms.
  //delay(3000);

  // Step in the other direction 1000 times.
  sd.setDirection(1);//clc
  sd2.setDirection(1);//clc
  //delayMicroseconds(100);
  for(unsigned int x = 0; x < 1000; x++)
  {
    sd.step();
    sd2.step();
    delayMicroseconds(StepPeriodUs);
  }

  // Wait for 300 ms.
  //delay(5000);
}
