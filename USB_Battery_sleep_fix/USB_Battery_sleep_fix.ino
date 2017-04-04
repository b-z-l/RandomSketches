#include "LowPower.h"

#define sleep_period 200000
#define wake_period 20000
#define sleep_cycles sleep_period / 8000
// need to wake every 11 cycles (88 seconds) for 100ms
#define battery_keepalive 11
#define transistor_pin 2

int sleep_count = sleep_cycles;
long int lastSleepTime = millis();

void setup()
{
  pinMode(transistor_pin, OUTPUT);
  // start turned on
  digitalWrite(transistor_pin, HIGH);
}

void loop()
{
  // Wake cycle


  // Sleep cycle
  if (millis() - lastSleepTime > wake_period)
  {
    digitalWrite(transistor_pin, LOW);
    for (int i = 0; i < sleep_cycles; i++)
    {
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
      
      // keepalive if 96 seconds have elapsed

      if ((i % 12) == 0)
      {
        digitalWrite(transistor_pin, HIGH);
        delay(20);
        digitalWrite(transistor_pin, LOW);
      }

    }
    digitalWrite(transistor_pin, HIGH);
    lastSleepTime = millis();
  }
}
