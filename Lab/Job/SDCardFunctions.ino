#include <Wire.h>
#include <LFlash.h>
#include <LStorage.h>

#define Drv LFlash

bool initSD() {
  if(!Drv.begin()) {
    Serial.println("Erro na Inicialiação do SD Card.");
    return true;
  } else {
    Serial.println("SD Card (Iniciado).");
    return true;
  }
}

void dataLog(String dataReaded) {  
    char file[16] = "";
    String fileName = getDateInt() + "_Sensor.log";

    Serial.print(getDatetime());
    Serial.print(" Arquivo: " + fileName);
    Serial.print(" - Dados :: ");
    Serial.print(getDatetime());
    Serial.print(" | ");
    Serial.println(dataReaded);

    fileName.toCharArray(file, 19);
    
    LFile dataFile = Drv.open(file, FILE_WRITE);
    if (dataFile) {
      dataFile.print(getTime());
      dataFile.println(dataReaded);
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


