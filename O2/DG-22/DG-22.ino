int gas_sensor = A0;
int buzz = 7;

const int variacao_maxima = 20;
float sensor_value_fx = 0;

const char* idGasA0 = "143";
const char* nameGasA0 = "DG-22";
int minimo = 0; 
int maximo = 30;

void setup() {

    Serial.begin(9600); //Baud rate
    pinMode(gas_sensor, INPUT); //Set gas sensor as input
    pinMode(buzz, OUTPUT);
    
}

void loop() {
  
    float sensorValue = analogRead(gas_sensor);

    float o2 = map(sensorValue, 0, 864, minimo, maximo);
    
    if (o2 < 18){
      digitalWrite(buzz, HIGH);
    }
    if (o2 > 19.5){
       digitalWrite(buzz, LOW);
    }
  
    Serial.print("%VOL  ");
    Serial.println(o2);
    
    Serial.println(
      String("EGAS") + ";" +
      String(nameGasA0) + ";" +
      String(idGasA0) + ";" +      
      String(o2 * 100000) + ";" + 
      String(millis())
    ); 
          
    int variacao = abs(((sensorValue - sensor_value_fx) / sensor_value_fx) * 100);
    
    //Definir minimo de variação para envio imediato, ou espera 
    if (variacao > variacao_maxima)  
    {
      delay(3000);      
    } 
    else {   
      delay(10000);
    }    
}
