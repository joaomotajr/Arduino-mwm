
void attachGPRS(const char* apn, const char* user, const char* pass) {

  Serial.println("Acessando Rede GRPS");
  while (!LGPRS.attachGPRS(apn, user, pass))
  {
    delay(500);
    Serial.print(".");
  }  
  Serial.println("Attached");
}

bool connGPRS(char host[], int port) {
  client.setTimeout(60000);
  if (client.connect(host, port)) {
    Serial.println("connected :: " + String(host) + ":" + String(port));
    return true;
  } else {  
    Serial.println("connection failed :: " + String(host) + ":" + String(port));
    return false;
  }
}

bool sendRequest(char* host, char* uri, String dataReaded) {
    Serial.println("Getting Data... From :: " + String(host) + String(uri) + String(dataReaded));

    // Make a HTTP request:
    client.print("GET ");    
    client.print(String(uri) + dataReaded);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(host);
    client.println("Connection: close");
    
    if (client.println() == 0) {
        Serial.println("Failed to send request");
        client.stop();
        return false;
    }    
    return true;
}

bool skipResponseHeaders() {
    Serial.println("Checking Header and Response.");
  
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
        Serial.print("Unexpected response: ");
        Serial.println(status);
        client.stop();
        return false;
    }
    
    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
        Serial.println("Invalid response");
        client.stop();
        return false;
    }
    return true;
}

bool testRead() {
    Serial.println("[Response:]");
    while (client.connected() || client.available())
    {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        String res = line.substring(0,41);
        Serial.println(res);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
    return true;
}

bool readReponseContent(struct clientData* clientData) {

  Serial.println("Reading and Parsing Results.");

  const size_t bufferSize = JSON_OBJECT_SIZE(1) + 41;
  DynamicJsonBuffer jsonBuffer(bufferSize);
  JsonObject& root = jsonBuffer.parseObject(client);

//  const size_t capacity = JSON_OBJECT_SIZE(2);
//  DynamicJsonBuffer jsonBuffer(capacity);
//  const char* json = "{\"type\":\"SUCCESS\",\"message\":\"PROCESSADO\"}";
//  JsonObject& root = jsonBuffer.parseObject(json);

  if (!root.success()) {
    Serial.println("JSON parsing failed!");
    return false;
  }

  // Here were copy the strings we're interested in using to your struct data
  strcpy(clientData->type, root["type"]);
  strcpy(clientData->message, root["message"]);
 
  return true;
}

// Print the data extracted from the JSON
void printclientData(const struct clientData* clientData) {
  Serial.print("type = ");
  Serial.println(clientData->type);
  Serial.print("message= ");
  Serial.println(clientData->message);
}

// Close the connection with the HTTP server
void disconnect() {
  Serial.println("Disconnect");
  client.stop();
}
