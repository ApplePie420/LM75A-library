# LM75A-library
LM75A is a great value-size sensor IC with 0.5°C accuracy and Overtemperature Shutdown feature. It talks throught I2C protocol so its great for use with Arduino! That´s why i wrote this **complete** library with access to **all of LM75A´s registers and functions.** I´ve seen few libraries for this IC but none of them had ability to set OS mode or HYST temp.


# Functions
You can find comments and more in [header file](LM75A.h) and [source code](LM75A.cpp)

### LM75A(address)
Creates a new instance of LM75A class, takes 1 argument, and that is I2C address of device (default is 0x48)

`LM75A tempSensor(0x48);`

### getTemp()
Returns measured temperature value as uint_16t (16bit unsigned int) in °C

`int measured_temp = tempSensor.getTemp();`

### shutdown(enable)
*Parameters:*
- true (set IC to sleep mode)
- false (wake up IC from sleep mode)

` tempSensor.shutdown(true); `

### setOSmode(mode)
*Parameters:*
- true (**Interrupt mode**, create an interrupt (short pulse for MCU) on OS pin (see datasheet))
- false (**Comparator mode**, stays at set value (by *setOSpolarity*) until temperature is lower than set)

`tempSensor.setOSmode(true);`

### setOSpolarity(polarity)
*Parameters:*
- true (active **HIGH**, sets pin HIGH when OS happens
- false (active **LOW**, sets pin LOW when OS happens

`tempSensor.setOSpolarity(true);`

### fault(queue)
*Parameters:*
- uint8_t queue (queue size, max readings before OS interrupt happens, available sizes: **1,2,4,6**)

`tempSensor.fault(2);`

### setOStemp(os_temp)
*Parameters:*
- uint8_t os_temp (Overtemperature Shutdown value, being constantly compared to measured value, is its greater or equal to this register, set an OS interrupt)

`tempSensor.setOStemp(50);`

### setHYSTtemp(hyst_temp)
*Parameters:*
- uint8_t hyst_temp (Set hysteresis value (some kind of error rate tolerance, see datasheet (i got well by using same or +-1°C as in setOStemp())))

`tempSensor.setHYSTtemp(50);`

### getOStemp()
For debugging purposes, returns content of OStemp register (to see if its set correctly)

`int OStemp_content = tempSensor.getOStemp();`

### getHYSTtemp()
For debugging purposes, returns content of OShyst register (to see if its set correctly)

`int OShyst_content = tempSensor.getHYtemp();`

### getTempF()
Returns measured temperature value as uint_16t but in °F 

`int tempF = tempSensor.getTempF();`

## Sample code
```
#include <LM75A.h>

LM75A sensor(0x48); //create instance of this library with name "sensor" and at address 0x48

void setup() {
  Serial.begin(9600); //begin Serial

  sensor.setOSmode(false);
  sensor.setOStemp(33); //set OS temp to 33°C (triggers a COMPARE output that we set)
  sensor.setHYSTtemp(32); //set hysteresis temp to 32°C to get rid of errors

  Serial.println(sensor.getOStemp()); //print content of OStemp register to see if its set correctly
  Serial.println(sensor.getHYSTtemp()); //print content of OShyst register to see if its set correctly
  Serial.println("-----");  //spacer
}

void loop() {
  Serial.println(sensor.getTemp()); //print measured temperature
  delay(1000);  //1s delay
}
```

###### *Also, i tested every function of library and it worked BUT, if you have any problems be sure to create new issue!*
