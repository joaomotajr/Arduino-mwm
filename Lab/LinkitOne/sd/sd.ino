#include <LFlash.h>
#include <LSD.h>
#include <LStorage.h>

//#define Drv LFlash          // use Internal 10M Flash 
 #define Drv LSD           // use SD card

char file[15] = "";

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  
  if(!Drv.begin()) {
    Serial.println("Error initalizing memory.");  
    while(true);
  }
}

void loop()
{ 
  
//    String str = "Joao Mota Junior";    
//    Serial.println(str);
//            
//    LFile dataFile = Drv.open("datalog.txt", FILE_WRITE);
//    if (dataFile)
//    {
//      dataFile.println(str);
//      dataFile.close();
//      Serial.println("File written.");
//    }
//    else Serial.println("Error opening file.");
}
