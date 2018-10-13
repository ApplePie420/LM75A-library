#include "LM75A.h"
#include <Wire.h>

//Initialization fnc
LM75A::LM75A(uint8_t address) {
  _address = address;
  Wire.begin(address);
}

///*****************///
///PRIVATE FUNCTIONS///
///*****************///

//Will reset configuration register except given values
void LM75A::resetConfigRegister(uint8_t defaultSettings, uint8_t exceptAddress) {
  Wire.beginTransmission(_address);
  Wire.write(0x01);
  Wire.write(defaultSettings & exceptAddress);
  Wire.endTransmission();
}

//Will set given bits in configuration register
void LM75A::setConfigRegister(uint8_t defaultSettings, uint8_t setting) {
  Wire.beginTransmission(_address);
  Wire.write(0x01);
  Wire.write(defaultSettings | setting);
  Wire.endTransmission();
}

//Returns content of config register
uint8_t LM75A::getConfigRegisterSettings() {
  uint8_t settings_temp;
  Wire.requestFrom(_address, 1);
  while (Wire.available()) {
    settings_temp = Wire.read();
  }
  return settings_temp;
}

///****************///
///GLOBAL FUNCTIONS///
///****************///

//Returns 16b int with temp value
uint16_t LM75A::getTemp() {
  uint16_t receivedTemp = 0;
  Wire.beginTransmission(_address);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.requestFrom(_address, 2);
  while (Wire.available()) {
    receivedTemp = Wire.read() | (Wire.read() >> 8);
  }
  return receivedTemp;
}

//Set shutdown feature (1 = enabled, 0 - disabled)
void LM75A::shutdown(bool enable) {
  uint8_t settings = getConfigRegisterSettings();

  if(enable) {
    setConfigRegister(settings, 0x01);
  } else {
    resetConfigRegister(settings, 0xFE);
  }
}

//Set OS (Overtemperature Shutdown) mode (1 = interrupt, 0 = compare)
void LM75A::setOSmode(bool mode) {
  uint8_t settings = getConfigRegisterSettings();

  if(mode) {
    setConfigRegister(settings, 0x02);
  } else {
    resetConfigRegister(settings, 0xFD);
  }
}

//Set OS polarity (1 = active HIGH, 2 = active LOW)
void LM75A::setOSpolarity(bool polarity) {
  uint8_t settings = getConfigRegisterSettings();

  if(polarity) {
    setConfigRegister(settings, 0x04);
  } else {
    resetConfigRegister(settings, 0xFB);
  }
}

//Set maximum fault queue vefore setting OS flag (1,2,4,6 = available queue length)
void LM75A::fault(uint8_t queue) {
  uint8_t settings = getConfigRegisterSettings();

  switch (queue) {
    case 1:
      setConfigRegister(settings, 0x00);
      break;

    case 2:
      setConfigRegister(settings, 0x08);
      break;

    case 4:
      setConfigRegister(settings, 0x10);
      break;

    case 6:
      setConfigRegister(settings, 0x18);
      break;
  }
}

//Sets OS temperature (16b int = desired OS temperature)
void LM75A::setOStemp(uint8_t os_temp) {
  Wire.beginTransmission(_address);
  Wire.write(0x03);
  Wire.write(os_temp);
  Wire.endTransmission();
}

//Set hysteresis temperature (set to +-1°C of OStemp) (16b int = desired HYST temperature)
void LM75A::setHYSTtemp(uint8_t hyst_temp) {
  Wire.beginTransmission(_address);
  Wire.write(0x02);
  Wire.write(hyst_temp);
  Wire.endTransmission();
}

//DEBUG - Returns content of OStemp register
uint16_t LM75A::getOStemp() {
  uint16_t received = 0;

  Wire.beginTransmission(_address);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.requestFrom(_address, 2);
  while (Wire.available()) {
    received = Wire.read() | (Wire.read() >> 8);
  }
  return received;
}

//DEBUG - Returns content of HYSTtemp register
uint16_t LM75A::getHYSTtemp() {
  uint16_t received = 0;

  Wire.beginTransmission(_address);
  Wire.write(0x02);
  Wire.endTransmission();

  Wire.requestFrom(_address, 2);
  while (Wire.available()) {
    received = Wire.read() | (Wire.read() >> 8);
  }
  return received;
}

//Return measured temperature in °F (Farnheit)
uint16_t LM75A::getTempF() {
  uint16_t temp_local = getTemp();
  return temp_local * (9/5) + 32;
}
