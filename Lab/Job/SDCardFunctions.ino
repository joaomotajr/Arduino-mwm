#include <LDateTime.h>
#include <Wire.h>
#include <LFlash.h>
#include <LStorage.h>

#define Drv LFlash

char dataLog[] = "datalog.txt";

datetimeInfo t;
unsigned int rtc;

bool initSD() {
  if(!Drv.begin()) {
    Serial.println("Erro na Inicialiação do SD Card.");
    return true;
  } else {
    Serial.println("SD Card (Iniciado).");
    return true;
  }
}

void putLog(String dataReaded) {  
    log("LogFile :: ", false);
    getDatetime();
    Serial.print(" | ");
    Serial.println(dataReaded);

    char file[15] = "";
    LDateTime.getTime(&t);
    String fileName = String(t.year) + String(t.mon) + String(t.day) + "_Sensor.log";    
    log("Arquivo : " + fileName, true);        

    fileName.toCharArray(file, 19);
//    Serial.println(file);
    
    LFile dataFile = Drv.open(file, FILE_WRITE);
    if (dataFile) {
      String localHora = String(t.hour) + ":" + String(t.min) + ":" + String(t.sec) + " ";
      dataFile.print(localHora);
      dataFile.println(dataReaded);
      dataFile.close();    
    } else {
      log("Erro ao abrir " + fileName , true);
    }
}

void getDatetime() {

  LDateTime.getTime(&t);
  LDateTime.getRtc(&rtc);

  Serial.print(t.day);   
  Serial.print("/");
  if(t.mon < 10) Serial.print("0");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.year);
  Serial.print(" ");
  Serial.print(t.hour);
  Serial.print(":");
  if(t.min < 10) Serial.print("0");
  Serial.print(t.min);
  Serial.print(":");
  if(t.sec < 10) Serial.print("0");
  Serial.print(t.sec);     
}

void log(String p, boolean n ) {

  LDateTime.getTime(&t);
  LDateTime.getRtc(&rtc);

  Serial.print(t.day);   
  Serial.print("/");
  if(t.mon < 10) Serial.print("0");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.year);
  Serial.print(" ");
  Serial.print(t.hour);
  Serial.print(":");
  if(t.min < 10) Serial.print("0");
  Serial.print(t.min);
  Serial.print(":");
  if(t.sec < 10) Serial.print("0");
  Serial.print(t.sec); 
  Serial.print(" ");
  Serial.print(p);  
  if (n) Serial.println("");
}


void setDatetime() {
  datetimeInfo now;
  now.year = 2019;
  now.mon = 2;
  now.day = 22;
  now.hour = 0;
  now.min = 35;
  LDateTime.setTime(&now);
}
