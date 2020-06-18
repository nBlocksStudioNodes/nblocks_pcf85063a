#include "pcf85063a.h"
#include "mbed.h"
#define SLAVE_ADDRESS 0xA2

pcf85063a::pcf85063a(PinName SDA,PinName SCL): _i2c(SDA,SCL){
    
    
    
    
}

pcf85063a::~pcf85063a(){
    
}

/**
  * @brief  This function converts the decimal date/time values to BCD and sends to RTC via i2c
  * @param  seconds,minutes,hours,days,weekday,month,year
  * @retval NA
  */

void pcf85063a :: set_datetime(char sec,char mins,char hours,char day,char weekday,char month, char year){
    
    int address = SLAVE_ADDRESS;
    
    
    char cmd[2];
    char current_time[8];
    
    cmd[0] = 0x00; // control_1 register
    cmd[1] = 0x01; // 24 hour mode 12.5 PF 
    
    current_time[0] = 0x04;//register address of seconds
    
    current_time[1] = (sec/10 * 16)+(sec % 10) ;//seconds
    current_time[2] = (mins/10 * 16)+(mins % 10) ;
    current_time[3] = (hours/10 * 16)+(hours % 10) ;
    current_time[4] = (day/10 * 16)+(day % 10) ;
    current_time[5] = weekday;// no conversion necessary as it never greatet than 6
    current_time[6] = (month/10 * 16)+(month % 10) ;
    current_time[7] = (year/10 * 16)+(year % 10) ;
    
    _i2c.write(address, &cmd[0], 2, false);
    _i2c.write(address, &current_time[0],8,false);    
    
    
}

/**
  * @brief  extracts date and time from RTC using i2c
  * @param  NA
  * @retval NA
  */

void pcf85063a :: get_datetime(){
    
    int address = SLAVE_ADDRESS;
    char cmd[1];
    
    cmd[0] = 0x04;
    
    _i2c.write(address, &cmd[0], 1, false);
        
    _i2c.read(address,&buffer[0],7, false);// 0xA3
    
}

/**
  * @brief  This function converts the binary coded decimal value to a seconds integer value
  * @param  NA
  * @retval time in seconds
  */

uint8_t pcf85063a :: get_seconds(){
    
    uint8_t BCD_sec = buffer[0];
    
    uint8_t tens_place;
    uint8_t unit_place; 
    uint8_t seconds;
    
    unit_place = BCD_sec & 0x0F;
    
    tens_place = (BCD_sec >> 4) & 0x07;  // 0x07 because there is a status bit in the MSB that could corrupt the number
    
    seconds = (tens_place * 10) + unit_place;
    
    return seconds;
    
}

/**
  * @brief  This function converts the binary coded decimal value to an minutes integer value
  * @param  NA
  * @retval time in seconds
  */

uint8_t pcf85063a :: get_minutes(){
    
    uint8_t BCD_mins = buffer[1];
    
    uint8_t tens_place;
    uint8_t unit_place; 
    uint8_t minutes;
    
    unit_place = BCD_mins & 0x0F;
    
    tens_place = (BCD_mins >> 4) & 0x07;
    
    minutes = (tens_place * 10) + unit_place;
    
    return minutes;
    
    
    
}

/**
  * @brief  This function converts the binary coded decimal value to an hour integer value
  * @param  NA
  * @retval time in hours
  */

uint8_t pcf85063a :: get_hour(){
    
    uint8_t BCD_hour = buffer[2];
    
    uint8_t tens_place;
    uint8_t unit_place; 
    uint8_t hour;
    
    unit_place = BCD_hour & 0x0F;
    
    tens_place = (BCD_hour >> 4) & 0x03;
    
    hour = (tens_place * 10) + unit_place;
    
    return hour;
       
    
}

/**
  * @brief  This function converts the binary coded decimal value to an day integer value
  * @param  NA
  * @retval time in hours
  */

uint8_t pcf85063a :: get_day(){
    
    uint8_t BCD_day = buffer[3];
    
    uint8_t tens_place;
    uint8_t unit_place; 
    uint8_t day;
    
    unit_place = BCD_day & 0x0F;
    
    tens_place = (BCD_day >> 4) & 0x03;
    
    day = (tens_place * 10) + unit_place;
    
    return day;
    
}

/**
  * @brief  This function returns the day of the week
  * @param  
  * @retval day of the week
  */


uint8_t pcf85063a ::  get_weekday(){
    
    uint8_t weekday = buffer[4];
    
    uint8_t day_of_week;
    
    day_of_week = weekday; // just for consistency will add code later for returning a string
    
    return day_of_week;
    
    
    
}

/**
  * @brief  This function converts the binary coded decimal value to a month  integer value
  * @param  
  * @retval month of the year
  */

uint8_t pcf85063a :: get_month(){
    
    uint8_t BCD_month = buffer[5];
    
    uint8_t tens_place;
    uint8_t unit_place; 
    uint8_t month;
    
    unit_place = BCD_month & 0x0F;
    
    tens_place = (BCD_month >> 4) & 0x01;
    
    month = (tens_place * 10) + unit_place;
    
    return month;
    
    
}

/**
  * @brief  This function converts the binary coded decimal value to a year  integer value
  * @param  NA
  * @retval year
  */

uint8_t pcf85063a :: get_year(){
    
    uint8_t BCD_year = buffer[6];
    
    uint8_t tens_place;
    uint8_t unit_place; 
    uint8_t year;
    
    unit_place = BCD_year & 0x0F;
    
    tens_place = (BCD_year >> 4) & 0x0F; // all 8 bits of register is used
    
    year = (tens_place * 10) + unit_place;
    
    return year;
    
    
}


