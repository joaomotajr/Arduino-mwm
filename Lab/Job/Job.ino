#include <ArduinoJson.h>
#include <LGPRS.h>
#include <LGPRSClient.h>
#include <Nanoshield_ADC.h>

const char* apn = "claro.com.br";
const char* user = "claro";
const char* pass = "claro";

char host[] = "177.144.134.145";
char uri[] = "/api/historic/SaveByPositionIOT/";
int port = 8090;

const char* idFlow = "146";
float highValue = 12;
float lowValue = 0;

LGPRSClient client;

void setup() {
    Serial.begin(9600);
    
    pinMode(13, OUTPUT);
    warningLight(2);

    initSD();
    setDatetime();
    initADC();
    
    attachGPRS(apn, user, pass);
    if(connGPRS(host, port)) {
      initFeedback();
    }
}

void loop() {

  float flow = processADC();
  
  if(connGPRS(host, port)) {
    String dataReaded = String(idFlow) + "/" + String(flow*100000).c_str();
    if(sendRequest(host, uri, dataReaded)) {
      if(skipResponseHeaders()) {
        checkReponse();
      }
    }
  }
  
  disconnect();
  delay(60000);     
}

void initFeedback() { 
  Serial.println("---------------------------------------------");
  log("Processamento Iniciado. ", true);
  Serial.println("---------------------------------------------");
  Serial.println("");
  warningLight(2);  
}

