#include <LGPRS.h>
#include <LGPRSClient.h>
#define SITE_URL "arduino.cc"
LGPRSClient client;
void setup()
{
  Serial.begin(9600);
  Serial.println("Try to connect..");
  
  delay(1000);
  while(!LGPRS.attachGPRS("claro.com.br", "claro", "claro"))
  {
    Serial.println("wait for SIM card ready");
    delay(1000);
  }
  Serial.print("Connecting to : " SITE_URL "...");
  if(!client.connect(SITE_URL, 80))
  {
    Serial.println("FAIL!");
    return;
  }
   Serial.println("done");
   Serial.print("Sending GET request...");
   client.println("GET / HTTP/1.1");
   client.println("Host: " SITE_URL ":80");
   client.println();
   Serial.println("done");
}
void loop()
{
 int v;
 while(client.available())
 {
 v = client.read();
 if (v < 0)
 break;
 Serial.write(v);
 }
 delay(500);
}
