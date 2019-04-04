char idDevice[] = "156";
float highValue = 12;
float lowValue = 0;

void setup() {
    Serial.begin(9600);     
}

void loop() {
    float sensorVolt;

    //Leitura do conversor
    int sensorValue = analogRead(A0);    
    sensorVolt=(float)sensorValue/1024*5.0;
    
    //Scalling V to mA (0 a 5)v para (4 a 20)mA
    float mA = 16 * (sensorVolt / 5) + 4;
    float mA_ = (mA*100)/100;

    //Arredonda o minimo
    if(mA_ >= 3.97 && mA_ <= 4) {
      mA_ = 4.0;
    }

    //Conversão de voltagem em medida do gás faltando    
    Serial.println(
      String("EGAS") + ";" +
      String(idDevice) + ";" +
      String(sensorValue) + ";" +     
      String(sensorVolt) + ";" + 
      String(mA_) + ";" +       
      String(millis())
    ); 

   delay(3000);   
}
