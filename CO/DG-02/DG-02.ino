int gas_sensor = A0;
int buzz = 10;

const int variacao_maxima = 10;
int sensor_value_fx = 0;

const char* idGasA0 = "120";
const char* nameGasA0 = "DG-02";
int minimo = 0;
int maximo = 100;



//cablibration phase
void setup() {

  Serial.begin(9600); //Baud rate
  pinMode(gas_sensor, INPUT); //Set gas sensor as input
  pinMode(buzz, OUTPUT);
}


void loop() {
  byte i = 0;                                    //  Variável para usar no for
  long accuml = 0;                               //  Variável para guardar o valor acumulado da temperatura
  long val = 0;                                  //  Variável para guardar o valor lido da temperatura

  for ( i = 0; i < 50; i++)                      // for de 50 vezes:  de 0 a 49 = 50 vezes

  {

    float val = analogRead(gas_sensor) ;                         // le o valor da temperatura

    accuml = accuml + val;        // Acumula 50 vezes as temperatura lidas

  }

  float val_M = accuml / 50;                 //  calcula a temperatura média das ultima 50 leituras


  float CO = map(val_M, 14, 224, minimo, maximo);

  if (CO >= 40) {
    digitalWrite(buzz, HIGH);
  }
  if (CO <= 25) {
    digitalWrite(buzz, LOW);
  }


  Serial.println(
    String("EGAS") + ";" +
    String(nameGasA0) + ";" +
    String(idGasA0) + ";" +
    String(CO * 100000) + ";" +
    String(millis())
  );

//  Serial.println(val_M);
//  Serial.println(CO);

  int variacao = abs(((val_M - sensor_value_fx) / sensor_value_fx) * 100);

  //Definir minimo de variação para envio imediato, ou espera
  if (variacao > variacao_maxima)
  {
    delay(3000); // mudar para 3000
  }
  else {
    delay(10000); // mudar para 10000
  }

  sensor_value_fx = val_M;
}
