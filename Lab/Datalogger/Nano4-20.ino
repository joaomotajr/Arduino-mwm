#include <Nanoshield_ADC.h>

Nanoshield_ADC adc;
int channel = 0;

void initADC() {
  Serial.println("---------------------------------------------");
  Serial.print("Read 4-20mA sensor (channel A");
  Serial.print(channel);
  Serial.println(") [Aberto]");
  adc.begin(); 
  adc.setGain(GAIN_TWO);
  Serial.println("Sensor ADC 4~20 [Iniciado]");
}

float processADC() {  
  float mA = adc.read4to20mA(channel);
  float mA_ = (mA*100)/100;
  
  if(mA_ >= 3.97 && mA_ <= 4) {
    mA_ = 4.0;
  }
    
  float flow =  lowValue + (highValue - lowValue) * (mA_ - 4) / 16;  
  log("Medição -> 4~20: " + String(mA_) + " FLOW: " + String(flow), true);

  if(logLevel >= 1) {
    dataLog(String(flow));
  }
  
  return flow;
}
