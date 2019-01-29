#include <Nanoshield_ADC.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>

const char* ssid = "jrnet2.4";
const char* password = "P@lmeiras";
const char* mqtt_server = "177.144.134.145";
const char* idFlow = "151";

//Wifi
WiFiClient wifiClient;
//MQTT
PubSubClient mqttClient(wifiClient);

float highValue = 12;
float lowValue = 0;

Nanoshield_ADC adc;
int channel = 0;

void setup()
{  
  Serial.begin(9600);
   
  Serial.print("Checking... WiFi");
  wifi_init();

  //Seta o servidor MQTT
  Serial.print("Iniciando MQTT");
  mqttClient.setServer(mqtt_server, 1883);   
  Serial.println("");
   
  Serial.print("16-bit ADC Nanoshield Test - Read 4-20mA sensor (channel A");
  Serial.print(channel);
  Serial.println(")");
  adc.begin();

  // Adjust gain to two (2.048V range) to get maximum resolution for 4-20mA range
  adc.setGain(GAIN_TWO);
}

void loop()
{
  float mA = adc.read4to20mA(channel);
  Serial.print(mA, 6);
  Serial.println("mA");

  //Linearizing
  float measure =  lowValue + (highValue - lowValue) * (mA - 4) / 16;
  Serial.print(measure, 6);
  Serial.println("m3Ltrs");

   if (!mqttClient.connected())
   {
      mqttConn();
   }

  Serial.println("Enviando Nivel ao E-gas - Device (Flow) :: " + String(idFlow) + " mA:: " + String(mA) +  "| Value:: " + String(measure)); 
  mqttClient.publish((idFlow), String(measure*100000).c_str(), true);
  
  delay(5000);
}
