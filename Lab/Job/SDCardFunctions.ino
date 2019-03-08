#include <Wire.h>
//#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>

//#define Drv LFlash
#define Drv LSD

bool initSD() {
  if(!Drv.begin()) {
    dataLogError("Erro na Inicialiação do SD Card.");
    return true;
  } else {
    Serial.println("SD Card (Iniciado).");
    return true;
  }
}

void dataLog(String dataReaded) {  
    char file[17] = "";
    String fileName = getDateInt() + "_Sensor.log";

    Serial.print(getDatetime());
    Serial.print(" Arquivo: " + fileName);
    Serial.print(" - Dados :: ");
    Serial.print(getDatetime());
    Serial.print(" | ");
    Serial.println(dataReaded);

    fileName.toCharArray(file, 20);
    
    LFile dataFile = Drv.open(file, FILE_WRITE);
    if (dataFile) {
      dataFile.print(getTime());
      dataFile.println(dataReaded);
      dataFile.close();    
    } else {
      log("Erro ao abrir " + fileName , true);
    }
}

void dataLogError(String error) {  

    log(error, true);  
    char file[13] = "";
    String fileName = "LogErro.log";
    fileName.toCharArray(file, 14);
    
    LFile dataFile = Drv.open(file, FILE_WRITE);
    if (dataFile) {
      dataFile.print(getDatetime());
      dataFile.print(" ");
      dataFile.println(error);
      dataFile.close();    
    } else {
      log("Erro ao abrir " + fileName , true);
    }
}

void log(String p, boolean n ) {
  Serial.print(getDatetime());
  Serial.print(" ");
  Serial.print(p);  
  if (n) Serial.println("");
}


