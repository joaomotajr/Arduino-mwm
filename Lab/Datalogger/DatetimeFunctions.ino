#include "Nanoshield_EEPROM.h"
#include "Nanoshield_RTC.h"
#include "Nanoshield_RTC.h"


datetimeInfo t;
Nanoshield_RTC rtc;

String getDatetime() {

  LDateTime.getTime(&t);
  LDateTime.getRtc(&rtc);

  String str = "";  
  if(t.day < 10) str += "0";
  str += t.day;   
  str += "/";
  if(t.mon < 10) str += "0";
  str += t.mon;
  str += "/";
  str += t.year;
  str += " ";
  if(t.hour < 10) str += "0";
  str += t.hour;
  str += ":";
  if(t.min < 10) str += "0";
  str += t.min;
  str += ":";
  if(t.sec < 10) str += "0";
  str += t.sec;
  return str;     
}

String getTime() {

  LDateTime.getTime(&t);
  LDateTime.getRtc(&rtc);

  String str = "";  
  if(t.hour < 10) str += "0";  
  str += t.hour;
  str += ":";
  if(t.min < 10) str += "0";
  str += t.min;
  str += ":";
  if(t.sec < 10) str += "0";
  str += t.sec;
  return str;     
}

String getDateInt() {
  LDateTime.getTime(&t);  
  String str = "";  
  str += t.year; 
  if(t.mon < 10) str += "0";
  str += t.mon;
  if(t.day < 10) str += "0";
  str += t.day;
  return str;
}

void setDatetime() {
  datetimeInfo now;
  now.year = 2019;
  now.mon = 2;
  now.day = 27;
  now.hour = 22;
  now.min = 23;
  LDateTime.setTime(&now);
}
