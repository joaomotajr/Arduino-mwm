#include <ArduinoJson.h>


char idDevice[] = "156";
float highValue = 12;
float lowValue = 0;
int logLevel = 3;   // 3 : Cartão, Envio e Check Response | 2 : Cartão e Envio | 1 : Cartão  | 0 : Só Leitura
int delayTime = 5000;


void setup() {
    Serial.begin(9600);
    
    pinMode(13, OUTPUT);
    warningLight(2);

    initSD();
    initADC();
    inicializa();            
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


