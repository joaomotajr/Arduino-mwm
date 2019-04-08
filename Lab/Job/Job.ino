#include <ArduinoJson.h>
#include <LGPRS.h>
#include <LGPRSClient.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

#define WIFI_AP "jrnet2.4"
#define WIFI_PASSWORD "P@lmeiras"
#define WIFI_AUTH LWIFI_WPA

char connType[] = "GPRS"; 
char host[] = "177.144.134.145";
char uri[] = "/api/historic/SaveByPositionIOT/";
char uriDate[] = "/api/util/time/";
int port = 8090;

char idDevice[] = "156";
float highValue = 12;
float lowValue = 0;
int logLevel = 3;   // 3 : Cartão, Envio e Check Response | 2 : Cartão e Envio | 1 : Cartão  | 0 : Só Leitura
int delayTime = 5000;
String measureType = "NIVEL";

LGPRSClient client;
LWiFiClient clientWiFi;

void setup() {
    Serial.begin(9600);
    
    pinMode(13, OUTPUT);
    warningLight(2);

    initSD();
    initADC();
    inicializa();            
}

void loop() {
  
  float value = processADC();

  if(String(connType) == "WIFI") {
    if(logLevel >= 2 && connClientWiFi(host, port)) {
      String dataReaded = String(idDevice) + "/" + String(value*100000).c_str();
      if(sendRequestUriWiFi(host, String(uri) + String(dataReaded))) {
        if(logLevel >= 3 && skipResponseHeadersWiFi()) {
          checkReponseWiFi();
        } 
      }
      disconnectWiFi();
    }
  } else if (String(connType) == "GPRS") {
    if(logLevel >= 2 && connGPRS(host, port)) {
      String dataReaded = String(idDevice) + "/" + String(value*100000).c_str();
      if(sendRequest(host, String(uri) + String(dataReaded))) {
        if(logLevel >= 3 && skipResponseHeaders()) {
          checkReponse();
        }
      }
      readSMS("Alive");      
      disconnect();
    }
  }   
  delay(delayTime);     
}

void inicializa() {
  Serial.println("---------------------------------------------");
  if(String(connType) == "WIFI") {
    Serial.println("Transmissão WiFi Selecionada.");
    attachWiFi();
    if(testClientWiFi(host, port)) {        
      setDatetimeOnlineWiFi();      
    }
  } else if (String(connType) == "GPRS") {
    Serial.println("Transmissão GPRS Selecionada.");      
    if(findGPRS()) {         
      setDatetimeOnline();
      initSMS();
    }     
  } else {
    Serial.println("Nenhuma Transmissão Configurada");
  }
  initFeedback();
}

void initFeedback() { 
  Serial.println("---------------------------------------------");
  Serial.println("Iniciando Processamento...");
  Serial.println("---------------------------------------------");
  Serial.println("");
  warningLight(2);  
}