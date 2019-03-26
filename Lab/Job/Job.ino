#include <ArduinoJson.h>
#include <LGPRS.h>
#include <LGPRSClient.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

#define WIFI_AP "jrnet2.4"
#define WIFI_PASSWORD "P@lmeiras"
#define WIFI_AUTH LWIFI_WPA

const char* connType = "WIFI";
const char* apn = "claro.com.br";
const char* user = "claro";
const char* pass = "claro";

char host[] = "177.144.134.145";
char uri[] = "/api/historic/SaveByPositionIOT/";
char uriDate[] = "/api/util/time/";
int port = 8090;

const char* idFlow = "145";
float highValue = 12;
float lowValue = 0;
int logLevel = 3;   // 3 : Cartão, Envio e Check Response | 2 : Cartão e Envio | 1 : Cartão  | 0 : Só Leitura
int delayTime = 5000;

const char* cellPhoneNumber = "11985340006";

LGPRSClient client;
LWiFiClient clientWiFi;

void setup() {
    Serial.begin(9600);
    
    pinMode(13, OUTPUT);
    warningLight(2);

    initSD();
    initADC();
    
    if(connType == "WIFI") {
      Serial.println("Transmissão WiFi Selecionada.");
      attachWiFi();
      if(testClientWiFi(host, port)) {
        initFeedback();
        setDatetimeOnlineWiFi();      
      }
    } else if (connType == "GPRS") {
      Serial.println("Transmissão GPRS Selecionada.");      
      attachGPRS(apn, user, pass);
      if(testGPRS(host, port)) {
        initFeedback();
        setDatetimeOnline();
        initSMS();
      }     
    } else {
      Serial.println("Nenhuma Transmissão Configurada");
    }    
}

void loop() {

  float flow = processADC();

  if(connType == "WIFI") {
    if(logLevel >= 2 && connClientWiFi(host, port)) {
      String dataReaded = String(idFlow) + "/" + String(flow*100000).c_str();
      if(sendRequestUriWiFi(host, String(uri) + String(dataReaded))) {
        if(logLevel >= 3 && skipResponseHeadersWiFi()) {
          checkReponseWiFi();
        } 
      }
      disconnectWiFi();
    }
  } else if (connType == "GPRS") {
    if(logLevel >= 2 && connGPRS(host, port)) {
      String dataReaded = String(idFlow) + "/" + String(flow*100000).c_str();
      if(sendRequest(host, String(uri) + String(dataReaded))) {
        if(logLevel >= 3 && skipResponseHeaders()) {
          checkReponse();
        }
      }
      readSMS("OK OK");
      disconnect();
    }
  }   
  delay(delayTime);     
}

void initFeedback() { 
  Serial.println("---------------------------------------------");
  Serial.println("Processamento Iniciado. ");
  Serial.println("---------------------------------------------");
  Serial.println("");
  warningLight(2);  
}
