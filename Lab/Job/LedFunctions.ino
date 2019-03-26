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

void ledOn() {
 digitalWrite(13, HIGH); 
}

void ledOff() {
 digitalWrite(13, LOW); 
}