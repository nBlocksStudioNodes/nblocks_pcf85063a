
/**
* @file     pcf85063a.h
* @brief    header file for pcf85063a RTC interface
* 
*
* @author   Ian Aherne
*
* @date     14/08/18
*/

#ifndef PCF85063A_H
#define PCF85063A_H

#include "mbed.h"

class pcf85063a{
    
    
    public:
    
        pcf85063a(PinName SDA,PinName SCL);
        ~pcf85063a();
        
        void set_datetime(char,char,char,char,char,char,char);
        void get_datetime();
        uint8_t get_seconds();
        uint8_t get_minutes();
        uint8_t get_hour();
        uint8_t get_day();
        uint8_t get_weekday();
        uint8_t get_month();
        uint8_t get_year();
		
        
    private:
        char buffer[7]; // for storing data that is extracted from RTC IC
        I2C _i2c;
    
};





#endif