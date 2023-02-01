#include <Arduino.h>
#include "sbus2h2.h"


// prepocet cisla z s.bus na
// usb min mid max pro 988-2012 us
// 172 - 993 - 1810
// výstup max 255 (254) hranice rozbehu asi 60
//


// hw piny pro ovladani motoru pres H mustek
// jeden je 0 druhy pwm
// pro opacny smer si vymeni role
void ChToH2::_init(int motApin, int motBpin)
{
    mot1pin = motApin;
    mot2pin = motBpin;

    kDown = (float)(SBUS_MID - SBUS_TRE - SBUS_MIN) / (float)(H2_MAX - H2_TRE);
    kUp = (float)(SBUS_MAX - SBUS_MID - SBUS_TRE) / (float)(H2_MAX - H2_TRE);

    setH2(SBUS_MID); // motor stoji
}

void ChToH2::setH2(int inValue)
{
    if (inValue >= SBUS_MID - SBUS_TRE && inValue <= SBUS_MID + SBUS_TRE)
    {
        ma = 0;
        mb = 0;
    }
    else if (inValue < SBUS_MID)
    {
        ma = 0;
        mb = (int)((float)(SBUS_MID - inValue) / kDown) + H2_TRE;
    }
    else
    {
        ma = (int)((float)(inValue - SBUS_MID) / kUp) + H2_TRE;
        mb = 0;
    }

    analogWrite(mot1pin, ma);
    analogWrite(mot2pin, mb);
}
#ifdef dbg
int ChToH2::getMa() {
  return ma;
}
int ChToH2::getMb() {
  return mb;
}
float ChToH2::getKUp() {
  return kUp;
}
float ChToH2::getKDn() {
  return kDown;
}
#endif
