  void wifi_init() {

    delay(10);
    Serial.println();
    
    Serial.print("Connecting to ");
    Serial.println(WIFI_AP);
  
    LWiFi.begin(); 
    
    while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(LWIFI_WPA, WIFI_PASSWORD))) 
    { 
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("WiFi connected");    
    Serial.println("");
}
//
//void mqttConn() {
//    // Loop até reconectar
//    while (!mqttClient.connected()) {
//        Serial.print("Aguardando Conexão MQTT ...");
//        
//        if (mqttClient.connect("wifiClient")) {
//            Serial.println("conectado");          
//        }
//        else {
//            Serial.print("Falha, rc=");
//            Serial.print(mqttClient.state());
//            Serial.println(" Tentando Novamente em 5 segundos...");
//          
//            delay(5000);
//        }
//    }  
//}
