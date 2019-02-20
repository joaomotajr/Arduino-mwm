#include <ArduinoJson.h>
#include <LGPRS.h>
#include <LGPRSClient.h>
#include <Nanoshield_ADC.h>

const char* apn = "claro.com.br";
const char* user = "claro";
const char* pass = "claro";

const unsigned long HTTP_TIMEOUT = 10000;  // max respone time from server
const size_t MAX_CONTENT_SIZE = 512;       // max size of the HTTP response

char host[] = "177.144.134.145";
char uri[] = "/api/historic/SaveByPositionIOT/";
int port = 8090;

const char* idFlow = "146";
float highValue = 12;
float lowValue = 0;

Nanoshield_ADC adc;
int channel = 0;

struct clientData {
  char type[8];
  char message[8];
};

LGPRSClient client;

void setup()
{
    Serial.begin(9600);
    while (!Serial) continue;

    pinMode(13, OUTPUT);
    warningLight(8);

    initADC();

    attachGPRS(apn, user, pass);
    connGPRS(host, port);    
}

void loop()
{
  float mA = adc.read4to20mA(channel);
  Serial.print(mA, 6);
  Serial.println("mA");

  //Linearizing
  float measure =  lowValue + (highValue - lowValue) * (mA - 4) / 16;

  Serial.print(measure, 6);
  Serial.println("m3Ltrs");
  
  if(connGPRS(host, port)) {
    String dataReaded = String(idFlow) + "/" + String(measure*100000).c_str();
    if(sendRequest(host, uri, dataReaded)) {
      if(skipResponseHeaders()) {
        clientData clientData;
        if(testRead()) {
        }
//        if(readReponseContent(&clientData)) {
//          printclientData(&clientData);
//        }
      }
    }     
  }

  warningLight(2);
  disconnect();
  delay(10000);
}
