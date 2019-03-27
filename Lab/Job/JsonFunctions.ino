void getConfig() {
  char fileName[] = "config.sys";
  String response = readFile(fileName);
  Serial.print(response);
  const size_t capacity = JSON_ARRAY_SIZE(4) + 8*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5);
  DynamicJsonBuffer jsonBuffer(capacity);        
  JsonObject& root = jsonBuffer.parseObject(response);

  if (!root.success()) {
    dataLogError("JSON com Erro!");        
  } else {    
    Serial.print(root["SYSTEM"]["connType"].as<char*>());
  }  
}
