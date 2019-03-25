void attachGPRS(const char* apn, const char* user, const char* pass) {

  Serial.print("Conectando a Rede GRPS ... ");
  while (!LGPRS.attachGPRS(apn, user, pass))
  {
    delay(500);
    Serial.print(".");
  }  
  Serial.println("[Conectado]");
}

bool testGPRS(char host[], int port) {
  client.setTimeout(60000);
  if (client.connect(host, port)) {
    Serial.println("Conectando ao Host :: " + String(host) + ":" + String(port) + "... [Conectado]");
    return true;
  } else {
    dataLogError("Falha na Conexão :: " + String(host) + ":" + String(port));  
    return false;
  }
}

bool connGPRS(char host[], int port) {  
  if (client.connect(host, port)) {
    log("Conectando ao Host :: " + String(host) + ":" + String(port) + "... [Conectado]", true);
    return true;
  } else {  
    dataLogError("Falha na Conexão :: " + String(host) + ":" + String(port));   
    return false;
  }
}

bool sendRequest(char* host, String uri) {

    log("Processando chamada REST [URI]: " + uri, true);

    client.print("GET ");    
    client.print(uri);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(host);
    client.println("Connection: close");
    
    if (client.println() == 0) {
        dataLogError("Falha na Requisição.");
        client.stop();        
        return false;
    }    
    return true;
}

bool sendRequestURI(char* host, char* uri) {

    log("Processando chamada REST [URI]: " + String(uri), true);

    client.print("GET ");    
    client.print(String(uri));
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(host);
    client.println("Connection: close");
    
    if (client.println() == 0) {
        dataLogError("Falha na Requisição.");
        client.stop();        
        return false;
    }    
    return true;
}

bool skipResponseHeaders() {
    log("Validando Response. ", false);
  
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
        dataLogError("Response [ERRO]: " + String(status));    
        return false;
    }
    
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
        dataLogError("Response [REST] Inválida.");        
        return false;
    }
    
    char endOfHeaders2[] = "\n";
    client.find(endOfHeaders2);
    Serial.println("[OK].");
    return true;
}

bool checkReponse() {
  
  log("Response: ", false);
  while (client.connected() || client.available())
  {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      String res = line.substring(0,41);
//    Serial.println(res);

      String respostaSistema = parseResult(res); 
      if (respostaSistema == "SUCCESS") {
        log("Sistema Atualizado: " + respostaSistema, true);
      } else {
        dataLogError("Sistema Não Atualizado: " + respostaSistema);
      }        
      break;
    }
  }    
   return true;
}

String parseResult(String response) {

  const size_t capacity = JSON_OBJECT_SIZE(2);
  DynamicJsonBuffer jsonBuffer(capacity);        
  JsonObject& root = jsonBuffer.parseObject(response);

  if (!root.success()) {
    dataLogError("JSON com Erro!");
    return "ERRO";
  } else {
    return String(root["type"].as<char*>());
  }  
}

void disconnect() {
  log("Fechando Ciclo.", true);
  Serial.println("");
  warningLight(1);
  client.stop();
}


