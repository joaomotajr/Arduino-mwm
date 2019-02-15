#include "LGSM.h"

const char* contact_no = "11985340006";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Initialize GSM for SMS");
  while (!LSMS.ready()){
      delay(1000);
      Serial.println(".");
  }
  Serial.println("GSM ready for sending SMS");

}

void loop() {  
//    send_low_water_SMS();
    delay(20000);
}

void send_low_water_SMS(){
    LSMS.beginSMS(contact_no);
 
    LSMS.print("Water tank is running low!");
    if (LSMS.endSMS()){
        Serial.println("SMS successfully sent");
    }
    else{
        Serial.println("SMS failed to send");
    }
}

