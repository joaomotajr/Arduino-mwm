int gas_sensor = A0;
int buzz = 10;

const int variacao_maxima = 20;
float sensor_value_fx = 0;

const char* idGasA0 = "122";
const char* nameGasA0 = "DG-04";
int minimo = 0; 
int maximo = 1000;

void setup() {

    Serial.begin(9600); //Baud rate
    pinMode(gas_sensor, INPUT); //Set gas sensor as input
    pinMode(buzz, OUTPUT);   
}

void loop() {

    float sensorValue = analogRead(gas_sensor);
 
    float co = map(sensorValue, 0, 1023, minimo, maximo);
    
    if (co < 18){
      digitalWrite(buzz, HIGH);
    }
    if (co > 19.5){
       digitalWrite(buzz, LOW);
    }

    Serial.println(
      String("EGAS") + ";" +
      String(nameGasA0) + ";" +
      String(idGasA0) + ";" +      
      String(co * 100000) + ";" + 
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

    sensor_value_fx = sensorValue;
}
