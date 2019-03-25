#include <ArduinoJson.h>

const char* apn = "claro.com.br";
const char* user = "claro";
const char* pass = "claro";

char host[] = "177.144.134.145";
char uri[] = "/api/historic/SaveByPositionIOT/";
char uriDate[] = "/api/util/time/";
int port = 8090;

const char* idFlow = "146";
float highValue = 12;
float lowValue = 0;

int logLevel = 2; //  3 : Cartão, Envio e Check Response | 2 : Cartão e Envio | 1 : Cartão  | 0 : Só Leitura
int delayTime = 5000;

const char* cellPhoneNumber = "11985340006";

LGPRSClient client;

void setup() {
    Serial.begin(9600);
    
    pinMode(13, OUTPUT);
    warningLight(2);

    initSD();
    initADC();
    initSMS();
    
    attachGPRS(apn, user, pass);
    if(testGPRS(host, port)) {
      initFeedback();
      setDatetimeOnline();
    }   
}

void loop() {

  float flow = processADC();
  
  if(logLevel >= 2 && connGPRS(host, port)) {
    String dataReaded = String(idFlow) + "/" + String(flow*100000).c_str();
    if(sendRequest(host, String(uri) + String(dataReaded))) {
      if(logLevel >= 3 && skipResponseHeaders()) {
        checkReponse();
      }
    }
  }
  
  disconnect();
  delay(delayTime);     
}

void initFeedback() { 
  Serial.println("---------------------------------------------");
  Serial.println("Processamento Iniciado. ");
  Serial.println("---------------------------------------------");
  Serial.println("");
  warningLight(2);  
}

