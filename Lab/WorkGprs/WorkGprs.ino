#include <ArduinoJson.h>
#include <LGPRS.h>
#include <LGPRSClient.h>

const char * apn = "claro.com.br";
const char * user = "claro";
const char * pass = "claro";

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
    Serial.println("Enviando dados...!");

    if (getHTTP(host, uri)) {
        Serial.println("Dados Enviados!");
        delay(10000);
    }
    else {
        Serial.println("Erro, aguardando nova conexão!");
        delay(30000);
        attachGPRS(apn, user, pass);
        connGPRS(host, port);
    }

    Serial.println("Fim Ciclo.");
}
