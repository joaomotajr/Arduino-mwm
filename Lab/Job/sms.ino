#include "LGSM.h"
#include <LTask.h>

bool initSMS() {
  int count = 0;
  Serial.println("Initialize GSM for SMS");
  while (!LSMS.ready()) {
      delay(1000);
      Serial.println(".");
      count++;
      if(count > 10) {
          Serial.println("GSM NOT ready for sending SMS");
           return false;
      }  
  }
  Serial.println("GSM ready for sending SMS");
  return true;
}

void sendSMS(String message){
    LSMS.beginSMS(cellPhoneNumber);
 
    LSMS.print(message);
    if (LSMS.endSMS()) {
        log("SMS successfully sent", true);
    } else{
        log("SMS failed to send", true);
    }
}

bool readSMS(String resp) {
    char p_num[20];
    int len = 0;
    char dtaget[500];

    if(LSMS.available()) {    
        LSMS.remoteNumber(p_num, 20);
        log("There is new message.", true);
        
        log("Number: ", false);
        log(p_num, true);
        log("Content: ", false);

        while(true) {
            int v = LSMS.read();
            if(v < 0) break;

            dtaget[len++] = (char)v;
            Serial.print((char)v);
        }

        Serial.println();
        LSMS.flush(); 

        sendSMS(resp);
        
        if((dtaget[0] == 'O' && dtaget[1] == 'N') || (dtaget[0] == 'o' && dtaget[1] == 'n')) {
            ledOn;
        } else if((dtaget[0] == 'O' && dtaget[1] == 'F' && dtaget[2] == 'F') || (dtaget[0] == 'o' && dtaget[1] == 'f' && dtaget[2] == 'f')) {
            ledOff;
        }
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
        sendSMS(resp);
        
        if((dtaget[0] == 'O' && dtaget[1] == 'N') || (dtaget[0] == 'o' && dtaget[1] == 'n')) {
            ledOn;
        } else if((dtaget[0] == 'O' && dtaget[1] == 'F' && dtaget[2] == 'F') || (dtaget[0] == 'o' && dtaget[1] == 'f' && dtaget[2] == 'f')) {
            ledOff;
        }
        return content;
    }
}


