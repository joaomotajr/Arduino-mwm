#include "LGSM.h"
#include <LTask.h>

bool initSMS() {  
  int count = 0;
  Serial.println("---------------------------------------------");
  Serial.print("Inicializando GSM para SMS ....");
  while (!LSMS.ready()) {
      delay(1000);
      Serial.println(".");
      count++;
      if(count > 10) {
          Serial.println("FALHA!");
           return false;
      }  
  }
  Serial.println("PRONTO!");  
  return true;
}

void sendSMS(String message, char* n){
  LSMS.beginSMS(n); 
  LSMS.print(message);
  if (LSMS.endSMS()) {
      log("SMS enviado com sucesso", true);
  } else{
      log("SMS falha no envio", true);
  }
}

bool readSMS(String resp) {
    char p_num[20];
    int len = 0;
    char dtaget[500];

    if(LSMS.available()) {    
        LSMS.remoteNumber(p_num, 20);
        log("Novas mensagens [SMS].", true);
        
        log("Numero: ", false);
        log(p_num, true);
        log("Conteudo: ", false);

        while(true) {
            int v = LSMS.read();
            if(v < 0) break;

            dtaget[len++] = (char)v;
            Serial.print((char)v);
        }

        Serial.println();
        LSMS.flush(); 

        respondeSeNroValido(p_num, resp);
        
        if((dtaget[0] == 'O' && dtaget[1] == 'N') || (dtaget[0] == 'o' && dtaget[1] == 'n')) {
            ledOn;
        } else if((dtaget[0] == 'O' && dtaget[1] == 'F' && dtaget[2] == 'F') || (dtaget[0] == 'o' && dtaget[1] == 'f' && dtaget[2] == 'f')) {
            ledOff;
        }
    } else {
      log("Nenhum SMS recebido", true);
    }    
}

String getSMS(String resp) {
    char p_num[20];
    int len = 0;
    char dtaget[500];
    String content;

    if(LSMS.available()) {    
        LSMS.remoteNumber(p_num, 20);

        while(true) {
            int v = LSMS.read();
            if(v < 0) break;

            dtaget[len++] = (char)v;
            content += String((char)v);
        }
        LSMS.flush(); 
        respondeSeNroValido(p_num, resp);
        
        if((dtaget[0] == 'O' && dtaget[1] == 'N') || (dtaget[0] == 'o' && dtaget[1] == 'n')) {
            ledOn;
        } else if((dtaget[0] == 'O' && dtaget[1] == 'F' && dtaget[2] == 'F') || (dtaget[0] == 'o' && dtaget[1] == 'f' && dtaget[2] == 'f')) {
            ledOff;
        }
        return content;
    }
}

void respondeSeNroValido(char p_num[], String resp) {
  String nro = String(p_num);
  if(nro.length() > 6)
    sendSMS(resp, p_num);
}


