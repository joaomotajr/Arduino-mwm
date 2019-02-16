#include <ArduinoJson.h>
#include <LGPRS.h>
#include <LGPRSClient.h>

const char* apn = "claro.com.br";
const char* user = "claro";
const char* pass = "claro";

char host[] = "177.144.134.145";
char uri[] = "/api/historic/SaveByPositionUid2/144/166934";
int port = 8090;

int connGPRS(char host[], int port);
int getHTTP(char host[], char uri[]);
void attachGPRS(const char* apn, const char* user, const char* pass);

int result = 0;

LGPRSClient client;

void setup()
{
    // setup Serial po
    Serial.begin(115200);
    while (!Serial) continue;

    attachGPRS(apn, user, pass);
    result = connGPRS(host, port);
    
}

void loop()
{
    Serial.println("Enviando dados...!");

    if (getHTTP(host, uri)) {
        Serial.println("Dados Enviados!");
        delay(10000);
    }
    else {
        Serial.println("Erro, aguardando nova conexão!");
        delay(30000);
        attachGPRS(apn, user, pass);
        result = connGPRS(host, port);
    }

    Serial.println("Fim Ciclo.");
}


