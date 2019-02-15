void attachGPRS(char apn, char user, char pass) {

  Serial.println("Acessando Rede GRPS");
  while (!LGPRS.attachGPRS(apn, user, pass))
  {
    delay(500);
    Serial.print(".");
  }  
  Serial.println("Attached");
}

bool connGPRS(char host, char port) {

  client.setTimeout(60000);
  if (client.connect(host, port))
  {
    Serial.println("connected");
    return true;
  }
  else
  {  
    Serial.println("connection failed");
    return false;
  }
}

bool getHTTP(char server, char uri) {
// string getHTTP(char server, char uri, int id, float value) {

    Serial.println("Getting Data...");

    // Make a HTTP request:
    client.print("GET " + uri);    
    // client.print("GET ");    
    // client.print(uri +  String(id) +  "/"+ String(value ));
    client.println(" HTTP/1.1");
    client.print("Host: " + server);
    client.println("Connection: close");
    
    if (client.println() == 0) {
        Serial.println("Failed to send request");
        return false;
    }

    Serial.println("Receiving data...");

    // Check HTTP status
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
        Serial.print("Unexpected response: ");
        Serial.println(status);
        return false;
    }

    // Skip HTTP headers
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
        Serial.println("Invalid response");
        return false;
    }

    // Allocate JsonBuffer
    // Use arduinojson.org/assistant to compute the capacity.
    const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 60;
    DynamicJsonBuffer jsonBuffer(capacity);

    // Parse JSON object
    JsonObject& root = jsonBuffer.parseObject(client);
    if (!root.success()) {
        Serial.println("Parsing failed!");
        return false;
    }

    // Extract values
    Serial.println(F("Response:"));
    Serial.println(root["sensor"].as<char*>());
    Serial.println(root["time"].as<char*>());
    Serial.println(root["data"][0].as<char*>());
    Serial.println(root["data"][1].as<char*>());

    // Disconnect
    client.stop();

    return true;

}
