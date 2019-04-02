
String getMinDatetime() {
  
  rtc.read();
  String str = "";  
  if(rtc.getDay() < 10) str += "0";
  str += rtc.getDay();   
  str += "/";
  if(rtc.getMonth() < 10) str += "0";
  str += rtc.getMonth();
  str += " ";
  
  if(rtc.getHours() < 10) str += "0";
  str += rtc.getHours();
  str += ":";
  if(rtc.getMinutes() < 10) str += "0";
  str += rtc.getMinutes();
  str += ":";
  if(rtc.getSeconds() < 10) str += "0";
  str += rtc.getSeconds();
  return str;     
}


String getDatetime() {

  String str = "";  
  if(rtc.getDay() < 10) str += "0";
  str += rtc.getDay();   
  str += "/";
  if(rtc.getMonth() < 10) str += "0";
  str += rtc.getMonth();
  str += "/";
  str += rtc.getYear();
  str += " ";
  if(rtc.getHours() < 10) str += "0";
  str += rtc.getHours();
  str += ":";
  if(rtc.getMinutes() < 10) str += "0";
  str += rtc.getMinutes();
  str += ":";
  if(rtc.getSeconds() < 10) str += "0";
  str += rtc.getSeconds();
  return str;     
}

String getTime() {

  String str = "";  
  if(rtc.getHours() < 10) str += "0";  
  str += rtc.getHours();
  str += ":";
  if(rtc.getMinutes() < 10) str += "0";
  str += rtc.getMinutes();
  str += ":";
  if(rtc.getSeconds() < 10) str += "0";
  str += rtc.getSeconds();
  return str;     
}

String getDateInt() {

  String str = "";  
  str += rtc.getYear(); 
  if(rtc.getMonth() < 10) str += "0";
  str += rtc.getMonth();
  if(rtc.getDay() < 10) str += "0";
  str += rtc.getDay();
  return str;
}

void setDatetime() {
  
  Serial.println("-------------------------");
  Serial.println(" Nanoshield Serial Clock");
  Serial.println("-------------------------");
  Serial.println("");

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Failed starting RTC");
    while(true);
  };

  Serial.print("Current time:\n");
  
  // Set date and time
  rtc.writeYear(2018);
  rtc.writeMonth(03);
  rtc.writeDay(21);
  rtc.writeHours(14);
  rtc.writeMinutes(40);
  rtc.writeSeconds(00);
}
