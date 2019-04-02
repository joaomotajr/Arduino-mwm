char apn4[] = "gprs.oi.com.br";
char user4[] = "oi";
char pass4[] = "oi";

char apn3[] = "timbrasil.com.br";
char user3[] = "tim";
char pass3[] = "tim";

char apn2[] = "claro.com.br"; 
char user2[] = "claro"; 
char pass2[] = "claro"; 
 
char apn1[] = "zap.vivo.com.br"; 
char user1[] = "vivo"; 
char pass1[] = "vivo"; 

bool findGPRS() { 
     
  if(attachGPRS(apn1, user1, pass1)) { 
    if(testGPRS(host, port)) { 
      return true; 
    }
  }
 
  if(attachGPRS(apn2, user2, pass2)) {
    if(testGPRS(host, port)) {     
      return true; 
    }
  }
  
  if(attachGPRS(apn3, user3, pass3)) {
    if(testGPRS(host, port)) {     
      return true; 
    }
  }
  
  if(attachGPRS(apn4, user4, pass4)) {
    if(testGPRS(host, port)) {     
      return true; 
    }
  }
  
  if(logLevel > 0) 
    logLevel = 1; 
 
  Serial.println("Nenhuma conexão GRPS encontrada."); 
  return false; 
}

bool attachGPRS(char apn[], const char user[], const char pass[]) {
  Serial.print("Conectando a Rede GRPS: " + String(apn));
  int count = 0;
  while (!LGPRS.attachGPRS(apn, user, pass)) {
    delay(500);
    Serial.print(".");
    count++;
    if(count>60) {
      Serial.println("Sem Sinal GPRS da operadora " + String(apn));
      return false;
    }
  }  
  Serial.println(" [OK]");
  return true;
}

bool testGPRS(char host[], int port) {
  client.setTimeout(60000);
  Serial.print("Testando Conexão [GPRS] Host: " + String(host) + ":" + String(port) + " ");
  if (client.connect(host, port)) {
    Serial.println("[SUCESSO]");
    return true;
  } else {
    Serial.println("[FALHA]");  
    return false;
  }
}

bool connGPRS(char host[], int port) {
  log("Conectando [GPRS] Host: " + String(host) + ":" + String(port) + " ", false); 
  if (client.connect(host, port)) {
    Serial.println("[SUCESSO]");
    return true;
  } else {  
    Serial.println("[FALHA]");
    dataLogError("Falha Conexão [GPRS] Host: " + String(host) + ":" + String(port));   
    return false;
  }
}

bool sendRequest(char host[], String uri) {
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

bool checkReponse() {  
  log("Response: ", false);
  while (client.connected() || client.available()) {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      String res = line.substring(0,41);
//    Serial.println(res);

      String respostaSistema = parseResult(res); 
      if (String(respostaSistema) == "SUCCESS") {
        log("Sistema Atualizado: " + respostaSistema, true);
      } else {
        dataLogError("Sistema Não Atualizado: " + respostaSistema);
      }        
      break;
    }
  }    
   return true;
}

void disconnect() {
  log("Fechando Ciclo.", true);
  Serial.println("");
  warningLight(1);
  client.stop();
}


