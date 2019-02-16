
void attachGPRS(const char* apn, const char* user, const char* pass) {

  Serial.println("Acessando Rede GRPS");
  while (!LGPRS.attachGPRS(apn, user, pass))
  {
    delay(500);
    Serial.print(".");
  }  
  Serial.println("Attached");
}

int connGPRS(char host[], int port) {

  client.setTimeout(60000);
  if (client.connect(host, port))
  {
    Serial.println("connected");
    return 1;
  }
  else
  {  
    Serial.println("connection failed");
    return 0;
  }
}

int getHTTP(char* host, char* uri) {
    Serial.println("Getting Data... From :: " + String(host) + String(uri));

    // Make a HTTP request:
    client.print("GET ");    
    client.print(uri);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(host);
    client.println("Connection: close");
    
    if (client.println() == 0) {
        Serial.println("Failed to send request");
        client.stop();
        return 0;
    }

    Serial.println("Receiving data...");
    readClient();

//    // Check HTTP status
//    char status[32] = {0};
//    client.readBytesUntil('\r', status, sizeof(status));
//    if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
//        Serial.print("Unexpected response: ");
//        Serial.println(status);
//        client.stop();
//        return 0;
//    }
//
//    // Skip HTTP headers
//    char endOfHeaders[] = "\r\n\r\n";
//    if (!client.find(endOfHeaders)) {
//        Serial.println("Invalid response");
//        client.stop();
//        return 0;
//    }
//
//    // Allocate JsonBuffer
//    // Use arduinojson.org/assistant to compute the capacity.
//    const size_t capacity = 0 + 10;
//    DynamicJsonBuffer jsonBuffer(capacity);   
//
//    // Parse JSON object
//    JsonObject& root = jsonBuffer.parseObject(client);
//    if (!root.success()) {
//        Serial.println("Parsing failed!");
//        client.stop();
//        return 0;
//    }
//
//    // Extract values
//    Serial.println(F("Response:"));
//    Serial.println(root["sensor"].as<char*>());
//    Serial.println(root["time"].as<char*>());
//    Serial.println(root["data"][0].as<char*>());
//    Serial.println(root["data"][1].as<char*>());

    // Disconnect
    client.stop();

    return 1;
}

void readClient() {
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
