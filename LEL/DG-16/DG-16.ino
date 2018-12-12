int gas_sensor = A0;
int buzz = 10;

const int variacao_maxima = 5;
float sensor_value_fx = 0;

const char* idGasA0 = "137";
const char* nameGasA0 = "DG-16";
int minimo = 0; 
int maximo = 50;

void setup() {

    Serial.begin(9600); //Baud rate
    pinMode(gas_sensor, INPUT); //Set gas sensor as input
    pinMode(buzz, OUTPUT);   
}

void loop() {

    float sensorValue = analogRead(gas_sensor);
 
    float LEL = map(sensorValue, 464, 880, minimo, maximo);
    
    if (LEL >= 40){
      digitalWrite(buzz, HIGH);
    }
    if (LEL <= 25){
       digitalWrite(buzz, LOW);
   }

    Serial.println(
      String("EGAS") + ";" +
      String(nameGasA0) + ";" +
      String(idGasA0) + ";" +      
      String(LEL * 100000) + ";" + 
      String(millis())
    ); 
   
//    Serial.println(sensorValue);
//    Serial.println(LEL);
         
    int variacao = abs(((sensorValue - sensor_value_fx) / sensor_value_fx) * 100);
    
    //Definir minimo de variação para envio imediato, ou espera 
    if (variacao > variacao_maxima)  
    {
      delay(800); // mudar para 3000     
    } 
    else {   
      delay(1000); // mudar para 10000
    }

    sensor_value_fx = sensorValue;
}
