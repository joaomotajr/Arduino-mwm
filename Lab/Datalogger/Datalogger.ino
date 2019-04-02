#include <ArduinoJson.h>
#include <Wire.h>
#include <stdio.h>
#include "Nanoshield_LCD.h"
#include "Nanoshield_RTC.h"

char idDevice[] = "156";
float highValue = 12;
float lowValue = 0;
int logLevel = 3;   // 3 : Cartão, Envio e Check Response | 2 : Cartão e Envio | 1 : Cartão  | 0 : Só Leitura
int delayTime = 5000;

Nanoshield_RTC rtc;
Nanoshield_LCD lcd;

void setup() {
    Serial.begin(9600);
    
    pinMode(13, OUTPUT);
    warningLight(2);

    lcd.begin();
    lcd.clear();
    lcd.print("Inicializando...");

    initRTC();
    initSD();
    initADC();
    inicializa();
    lcd.clear();
}

void loop() {
  
  float flow = processADC();     
  delay(delayTime);     
}

void inicializa() {
  Serial.println("---------------------------------------------");  
  Serial.println("Nenhuma Transmissão Configurada"); 
  initFeedback();
}

void initFeedback() { 
  Serial.println("---------------------------------------------");
  Serial.println("Iniciando Processamento...");
  Serial.println("---------------------------------------------");
  Serial.println("");
  warningLight(2);  
}

bool initRTC() {
  Serial.println("---------------------------------------------");
  Serial.print("Módulo RTC sensor: ");

  if (!rtc.begin()) {
    Serial.println("[Falha]");
    return false;
  };
  rtc.read();
  Serial.println("[Iniciado]");
  return true;
}
