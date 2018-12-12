const char* idGasA0 = "116";
const char* nameGasA0 = "DG-200";
const int variacao_maxima = 20;

float sensor_volt_A0_FX = 0;

void setup() {
    Serial.begin(9600);     
}

void loop() {
    float sensor_volt_A0;
    
    int sensorValueA0 = analogRead(A0);
    sensor_volt_A0=(float)sensorValueA0/1024*5.0;

    long value = sensor_volt_A0*100000;
    
    //Conversão de voltagem em medida do gás faltando     
    
    Serial.println(
      String("EGAS") + ";" +
      String(nameGasA0) + ";" +
      String(idGasA0) + ";" +      
      String(value) + ";" + 
      String(millis())
    ); 

    int variacao = abs(((sensor_volt_A0 - sensor_volt_A0_FX) / sensor_volt_A0_FX) * 100);
    //Serial.println(String("Variação :: ") + String(variacao) + " %");
    
    //Definir minimo de variação para envio imediato, ou espera 
    if (variacao > variacao_maxima)  
    {
      delay(3000);      
    } 
    else {   
      delay(10000);
    }
    sensor_volt_A0_FX = sensor_volt_A0;
}
