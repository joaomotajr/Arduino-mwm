#include <LGPRS.h>
#include <LGPRSClient.h>

char server[] = "arduino.cc";
char path[] = "/asciilogo.txt";
int port = 80; // HTTP

LGPRSClient client;

void setup()
{
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  warningLight(8);
  
  Serial.println("Try to connect..");
  
  delay(1000);
  while(!LGPRS.attachGPRS("claro.com.br", "claro", "claro"))
  {
    Serial.println("wait for SIM card ready");
    delay(500);
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
