#include <LGPRS.h>
#include <LGPRSClient.h>
#include <Nanoshield_ADC.h>

const char* apn = "claro.com.br";
const char* user = "claro";
const char* pass = "claro";

char host[] = "arduino.cc";
char uri[] = "/asciilogo.txt";
int port = 80;

LGPRSClient client;

void setup()
{
    // setup Serial po
    Serial.begin(115200);
    while (!Serial) continue;

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
    else {
        Serial.println("Erro, aguardando nova conexão!");
        delay(30000);
        attachGPRS(apn, user, pass);
        connGPRS(host, port);
    }

}



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

    attachGPRS(apn, user, pass);    

    adc.begin();
    adc.setGain(GAIN_TWO);
  }
  disconnect();
  delay(10000);
}

char host[] = "177.144.134.145";
char uri[] = "/api/historic/SaveByPositionIOT/";
int port = 8090;
const char* idFlow = "146";
float highValue = 12;
float lowValue = 0;

Nanoshield_ADC adc;
int channel = 0;

    Serial.begin(9600);
    pinMode(13, OUTPUT);
    warningLight(2);

    initADC();

//    if(sendRequest(host, uri, dataReaded)) {
//      if(skipResponseHeaders()) {      
//        testRead();        
//      }
//    }     
  warningLight(2);