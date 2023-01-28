/*

    SBUS header (0x0F)
    16 servos (11 bits each) packed together into 22 bytes.
    Final byte showing if failsafe activated, plus channels 17,18
    SBUS final byte (0x00)


https://github.com/stm32duino/wiki/wiki/API
*/

//#define dbg


#include <Arduino.h>
#include "sbus.h"
#include "sbus2h2.h"

#define LED PC13

#define M1A PB0
#define M1B PB1

#define M2A PA6
#define M2B PA7

#define M3A PA0
#define M3B PA1

#define M4A PB6
#define M4B PB7



#if !defined(STM32_CORE_VERSION) || (STM32_CORE_VERSION < 0x01090000)
#error "Due to API change, this sketch is compatible with STM32_CORE_VERSION  >= 0x01090000"
#endif

HardwareSerial Serial2(PB11, PB10);

SBUS sbus(Serial2);
TIM_TypeDef *sbusTimer = TIM2; // TIM1 se pouziva na analog write

ChToH2 motor1(M1A, M1B);
ChToH2 motor2(M2A, M2B);
ChToH2 motor3(M3A, M3B);
ChToH2 motor4(M4A, M4B);






void
sbusProcess()
{
  sbus.process();
}

void setup()
{
  #ifdef dbg
  Initialize Serial
  #endif
  
  sbus.begin();
  pinMode(LED, OUTPUT); // RX failsafe indikator - svítí = failsafe

  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M3A, OUTPUT);
  pinMode(M3B, OUTPUT);
  pinMode(M4A, OUTPUT);
  pinMode(M4B, OUTPUT);

  digitalWrite(LED, 1);
  #ifdef dbg
      Serial.begin(1200);
  #endif
  
  HardwareTimer *MyTim = new HardwareTimer(sbusTimer);
  // timer
  MyTim->setOverflow(100, HERTZ_FORMAT); 
  MyTim->attachInterrupt(sbusProcess);
  MyTim->resume();
  
//  motor1 = new ChToH2(M1A, M1B);
}

void loop()
{
  motor1.setH2(sbus.getChannel(1));
  motor2.setH2(sbus.getChannel(2));
  motor3.setH2(sbus.getChannel(3));
  motor4.setH2(sbus.getChannel(4));


  #ifdef dbg
  // debug

        Serial.print(sbus.getChannel(1));
        Serial.print(" > ");
        Serial.print(motor1.getMa());
        Serial.print("  ");
        Serial.print(motor1.getMb());
        Serial.print(" > ");
        Serial.print(motor1.getKUp());
        Serial.print("  ");
        Serial.print(motor1.getKDn());
        Serial.print("\n");
  #endif

  // FAIL
  digitalWrite(LED, !sbus.getFailsafeStatus());

  delay(20);
}
