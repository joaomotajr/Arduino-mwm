#include <Wire.h>
#include <LFlash.h>
//#include <LSD.h>
#include <LStorage.h>

#define Drv LFlash
//#define Drv LSD

bool initSD() {
  if(!Drv.begin()) {
    dataLogError("Erro na Inicialiação do SD Card.");
    return true;
  } else {
    Serial.println("---------------------------------------------");
    Serial.println("SD Card [Iniciado].");
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
      dataFile.print("\t");
      dataFile.println(dataReaded);
      dataFile.close();    
    } else {
      dataLogError("Erro ao abrir " + fileName);
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

void writeFile(char* fileName, String content) {

  LFile dataFile = Drv.open(fileName, FILE_WRITE);
  if(dataFile) { 
    log("Gravando Arquivo ... " + String(fileName), true);
    dataFile.println(content);
    dataFile.close();
    log("Pronto!", true);
  } else {
    log("Erro ao abrir Arquivo ... " + String(fileName), true);
  }
}

String readFile(char fileName[]) {
  
  LFile dataFile = Drv.open(fileName);
  String content;
  char dtaget[800];
  int len = 0;

  if(dataFile) {
    dataFile.seek(0);
    log("Lendo Arquivo ... " + String(fileName), true);
    while (dataFile.available()) {
        int v = dataFile.read();
        if(v < 0) break;

        dtaget[len++] = (char)v;
        content += String((char)v);
    }
    dataFile.close();
    log("Arquivo Lido ... " + String(fileName), true);
    return content;
  } else {
    log("Erro ao abrir Arquivo ... " + String(fileName), true);
    return "";
  }
}

void log(String p, boolean n ) {
  Serial.print(getDatetime());
  Serial.print(" ");
  Serial.print(p);  
  if (n) Serial.println("");
}


