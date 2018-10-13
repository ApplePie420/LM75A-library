#ifndef LM75A_h
#define LM75A_h

#include "Arduino.h"
#include <Wire.h>

class LM75A {
  public:
    LM75A(uint8_t address);               //Begin communication with LM75A
    uint16_t getTemp();                   //Return temperature from sensor (in °C)
    void shutdown(bool enable);           //Set shutdown bit to 1 - enters sleep mode
    void setOSmode(bool mode);            //Set OS mode (1 - Interrupt, 0 - Comparator (see datasheet))
    void setOSpolarity(bool polarity);    //Set OS pin polarity (0 - active low, 1 - active high (see datasheet))
    void fault(uint8_t queue);            //Set OS fault queue (1,2,4,6 available (see datasheet))
    void setOStemp(uint8_t os_temp);      //Set OS trigger temperature
    void setHYSTtemp(uint8_t hyst_temp);  //Set Hysteresis temperature
    uint16_t getOStemp();                 //Return OS trigger temperature register settings (debug)
    uint16_t getHYSTtemp();               //Return HYST temperature register settings (debug)
    uint16_t getTempF();                  //Return temperature from sensor (in °F)

  private:
    void resetConfigRegister(uint8_t defaultSettings, uint8_t exceptAddress);   //Sets given bit from "exceptAddress" to 0 while keeping other bits as they were given from "defaultSettings"
    void setConfigRegister(uint8_t defaultSettings, uint8_t setting);           //Sets given bit from "setting" to 1 while keeping other bits as they were given from "defaultSettings"
    uint8_t getConfigRegisterSettings();                                        //Returns config register content
    uint8_t _address;                                                           //I2C address of device (0x48 default)
};

#endif
