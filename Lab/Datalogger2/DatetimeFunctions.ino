
String getMinDatetime() {
  
  DateTime now = rtc.now();
  String str = "";  
  if(now.day() < 10) str += "0";
  str += now.day();   
  str += "/";
  if(now.month() < 10) str += "0";
  str += now.month();
  str += " ";
  
  if(now.hour() < 10) str += "0";
  str += now.hour();
  str += ":";
  if(now.minute() < 10) str += "0";
  str += now.minute();
  str += ":";
  if(now.second() < 10) str += "0";
  str += now.second();
  return str;     
}


String getDatetime() {
  DateTime now = rtc.now();
  String str = "";  
  if(now.day() < 10) str += "0";
  str += now.day();   
  str += "/";
  if(now.month() < 10) str += "0";
  str += now.month();
  str += "/";
  str += now.year();
  str += " ";
  if(now.hour() < 10) str += "0";
  str += now.hour();
  str += ":";
  if(now.minute() < 10) str += "0";
  str += now.minute();
  str += ":";
  if(now.second() < 10) str += "0";
  str += now.second();
  return str;     
}

String getTime() {

  DateTime now = rtc.now();
  String str = "";  
  if(now.hour() < 10) str += "0";  
  str += now.hour();
  str += ":";
  if(now.minute() < 10) str += "0";
  str += now.minute();
  str += ":";
  if(now.second() < 10) str += "0";
  str += now.second();
  return str;     
}

String getDateInt() {

  DateTime now = rtc.now();
  String str = "";  
  str += now.year(); 
  if(now.month() < 10) str += "0";
  str += now.month();
  if(now.day() < 10) str += "0";
  str += now.day();
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
  
  //A linha abaixo ajusta o RTC com a data e hora do momento da compilacao
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //A linha abaixo permite ajustar manualmente a data e hora do RTC
  //Formato: DateTime(ano, mes, dia, hora, minuto, segundo)
  //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}
