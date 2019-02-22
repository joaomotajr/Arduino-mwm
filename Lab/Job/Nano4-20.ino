Nanoshield_ADC adc;
int channel = 0;

void initADC() {

  Serial.print("Read 4-20mA sensor (channel A");
  Serial.print(channel);
  Serial.println(") [Iniciado]");
  adc.begin();
 
  adc.setGain(GAIN_TWO);
}

float processADC() {  
  float mA = adc.read4to20mA(channel);
  float mA_ = (mA*100)/100;
  
  if(mA_ >= 3.98 && mA_ <= 3.99) {
    mA_ = 4.0;
  }
  
  putLog(String(mA_));
  
  float flow =  lowValue + (highValue - lowValue) * (mA_ - 4) / 16;  
  log("Medição -> 4~20: " + String(mA_) + " FLOW: " + String(flow), true);
  return flow;
}
