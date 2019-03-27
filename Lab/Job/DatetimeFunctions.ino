#include <LDateTime.h>

datetimeInfo t;
unsigned int rtc;

void setDatetimeOnline() {  
  Serial.println("---------------------------------------------");
  Serial.println("Inicializando Data, Aguarde ...");
  if(sendRequest(host, String(uriDate))) {
    if(skipResponseHeaders()) {
      checkReponseDate();
    }
  }
  Serial.println("Data Atualizada");   
}

void setDatetimeOnlineWiFi() {  
  Serial.println("---------------------------------------------");
  Serial.println("Inicializando Data");
  if(sendRequestUriWiFi(host, String(uriDate))) {
    if(skipResponseHeadersWiFi()) {
      checkReponseDateWiFi();
    }
  }
  Serial.println("Data Atualizada"); 
}

void parseDateResult(String response) {
  Serial.print("Parsing Data - ");
  const size_t capacity = JSON_OBJECT_SIZE(9);
  DynamicJsonBuffer jsonBuffer(capacity);        
  JsonObject& root = jsonBuffer.parseObject(response);

  if (!root.success()) {
    Serial.println("JSON com Erro!");    
  } else {    
    datetimeInfo now;
    now.year = String(root["year"].as<char*>()).toInt();
    now.mon = String(root["mon"].as<char*>()).toInt();
    now.day = String(root["day"].as<char*>()).toInt();
    now.hour = String(root["hour"].as<char*>()).toInt();
    now.min = String(root["min"].as<char*>()).toInt();
    LDateTime.setTime(&now);
    
    Serial.print("Data Aferida Online: ");
    Serial.println(getDatetime());
  }  
}

void checkReponseDate() {  
  Serial.print("Response Date: ");
  while (client.connected() || client.available()) {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      String res = line.substring(0,150);
      Serial.println(res);
      
      parseDateResult(res);
      break;
    }
  }   
}

void checkReponseDateWiFi() {  
  Serial.print("Response Date: ");
  while (clientWiFi.connected() || clientWiFi.available())
  {
    if (clientWiFi.available()) {
      String line = clientWiFi.readStringUntil('\n');
      String res = line.substring(0,150);
      Serial.println(res);
      
      parseDateResult(res);
      break;
    }
  }   
}

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
