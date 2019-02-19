#include <LGPRS.h>
#include <LGPRSClient.h>

char server[] = "177.144.134.145";
char path[] = "/api/historic/SaveByPositionIOT/144/166934";
int port = 8090;

LGPRSClient client;

void setup()
{
  // setup Serial po
  Serial.begin(115200);

  Serial.println("Conectando a Rede GPRS da CLARO");
  while (!LGPRS.attachGPRS("claro.com.br", "claro", "claro"))
  {
    delay(500);
    Serial.print(".");
  }

  // if you get a connection, report back via serial:
  Serial.print("Connect to ");
  Serial.println(server);
  if (client.connect(server, port))
  {
    Serial.println("connected");
    // Make a HTTP request:
    client.print("GET ");
    client.print(path);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
  }
  else
  {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.available() && !client.connected())
  {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for (;;)
      ;
  }
}
