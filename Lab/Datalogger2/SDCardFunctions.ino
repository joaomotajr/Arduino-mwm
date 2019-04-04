#include <SD.h>
const int chipSelect = 4;

bool initSD() {
  if(!SD.begin(chipSelect)) {
    dataLogError("Erro na Inicialiação do SD Card.");
    return true;
  } else {
    Serial.println("---------------------------------------------");
    Serial.println("SD Card [Iniciado].");
    return true;
  }
}

void dataLog(String dataReaded) {  
    
    String fileName = String(getDateInt()) + String(".log");
    int fileNameLen = fileName.length() +1;
    char file[fileNameLen];

    Serial.print(getDatetime());
    Serial.print(" Arquivo: " + fileName);
    Serial.print(" - Dados :: ");
    Serial.print(getDatetime());
    Serial.print(" | ");
    Serial.println(dataReaded);

    fileName.toCharArray(file, fileNameLen);
    
    File dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile) {
      dataFile.print(getTime());
      dataFile.print(";");
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
    
    File dataFile = SD.open(file, FILE_WRITE);
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

  File dataFile = SD.open(fileName, FILE_WRITE);
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
  
  File dataFile = SD.open(fileName);
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


