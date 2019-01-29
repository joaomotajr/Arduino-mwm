void wifi_init() {

    delay(10);
    Serial.println();
    
    Serial.print("Connecting to ");
    Serial.println(ssid);
  
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("");
}

void mqttConn() {
    // Loop até reconectar
    while (!mqttClient.connected()) {
        Serial.print("Aguardando Conexão MQTT ...");
        
        if (mqttClient.connect("wifiClient")) {
            Serial.println("conectado");          
        }
        else {
            Serial.print("Falha, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" Tentando Novamente em 5 segundos...");
          
            delay(5000);
        }
    }  
}
