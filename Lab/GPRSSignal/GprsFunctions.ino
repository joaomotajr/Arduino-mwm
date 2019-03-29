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
     
  attachGPRS(apn1, user1, pass1); 
  if(testGPRS(host, port)) { 
    return true; 
  }
 
  attachGPRS(apn2, user2, pass2); 
  if(testGPRS(host, port)) {     
    return true; 
  }

  attachGPRS(apn3, user3, pass3); 
  if(testGPRS(host, port)) {     
    return true; 
  }

  attachGPRS(apn4, user4, pass4); 
  if(testGPRS(host, port)) {     
    return true; 
  }
 
  if(logLevel > 0) 
    logLevel = 1; 
 
  Serial.println("Nenhuma conexão GRPS encontrada."); 
  return false; 
}

void attachGPRS(char apn[], const char user[], const char pass[]) {
  Serial.print("Conectando a Rede GRPS: " + String(apn));
  while (!LGPRS.attachGPRS(apn, user, pass)) {
    delay(500);
    Serial.print(".");
  }  
  Serial.println(" [OK]");
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

