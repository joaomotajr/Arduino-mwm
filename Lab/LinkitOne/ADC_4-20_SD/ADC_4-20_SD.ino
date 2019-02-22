#include <LDateTime.h>
#include <Nanoshield_ADC.h>
#include <Wire.h>
#include <LFlash.h>
#include <LStorage.h>

#define Drv LFlash

Nanoshield_ADC adc;
int channel = 0;
char dataLog[] = "datalog.txt";

datetimeInfo t;
unsigned int rtc;

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  warningLight(6);
  
  Serial.print("16-bit ADC Nanoshield - Read 4-20mA sensor (channel A");
  Serial.print(channel);
  Serial.println(")");
  
  adc.begin();
  adc.setGain(GAIN_TWO);

  initSD();  

  Serial.print("Data/Hora: ");
  getDatetime();
  Serial.println();
  
}

void loop() {
  float mA = adc.read4to20mA(channel);
  float mA_ = (mA*100)/100;
  
  if(mA_ >= 3.98 && mA_ <= 3.99) {
    mA_ = 4.0;
  }    
  
  putLog(String(mA_));
  
  warningLight(2);
  delay(1000);
}


void warningLight(int times) {  
  int i = 0;
  for(i = 0; i < times; i++) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);    
  }  
  delay(1000); 
}

bool initSD() {
  if(!Drv.begin()) {
    Serial.println("Erro na Inicialiação do SD Card.");
    return true;
  } else {
    Serial.println("SD Card (Iniciado).");
    return true;
  }
}

void putLog(String dataReaded) {  
    Serial.print("Log :: ");
    getDatetime();
    Serial.print(" | ");
    Serial.println(dataReaded);
            
//    LFile dataFile = Drv.open(dataLog, FILE_WRITE);
//    if (dataFile) {
//      dataFile.println(dataReaded);
//      dataFile.close();    
//    } else {
//      Serial.println("Erro ao abrir datalog.txt");
//    }
}

void getDatetime() {

  LDateTime.getTime(&t);
  LDateTime.getRtc(&rtc);

  Serial.print(t.day);   
  Serial.print("/");
  if(t.mon < 10) Serial.print("0");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.year);
  Serial.print(" ");
  Serial.print(t.hour);
  Serial.print(":");
  if(t.min < 10) Serial.print("0");
  Serial.print(t.min);
  Serial.print(":");
  if(t.sec < 10) Serial.print("0");
  Serial.print(t.sec);   
}

void setDatetime() {
  datetimeInfo now;
  now.year = 2019;
  now.mon = 2;
  now.day = 21;
  now.hour = 12;
  now.min = 23;
  LDateTime.setTime(&now);
}
