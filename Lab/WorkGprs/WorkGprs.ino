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

Nanoshield_ADC adc;
int channel = 0;

LGPRSClient client;

void setup()
{
    Serial.begin(9600);

    pinMode(13, OUTPUT);
    warningLight(2);

    initADC();

    attachGPRS(apn, user, pass);
    connGPRS(host, port);    
}

void loop()
{
  float mA = adc.read4to20mA(channel);
  float mA_ = (mA*100)/100;
  
  if(mA_ >= 3.98 && mA_ <= 3.99) {
    mA_ = 4.0;
  }
    
  Serial.print(mA_);
  Serial.println("mA");

  //Linearizing
  float measure =  lowValue + (highValue - lowValue) * (mA_ - 4) / 16;

  Serial.print(measure, 6);
  Serial.println("m3Ltrs");
  
  if(connGPRS(host, port)) {
    String dataReaded = String(idFlow) + "/" + String(measure*100000).c_str();
//    if(sendRequest(host, uri, dataReaded)) {
//      if(skipResponseHeaders()) {      
//        testRead();        
//      }
//    }     
  }
  warningLight(2);
  disconnect();
  delay(10000);
}
