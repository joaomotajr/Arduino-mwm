#include "LTask.h"
#include "vmcell.h"

// Cellular Network information refresh delay
const int loop_delay_ms = 5000;



void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  init_cell_register();
}

/*
	- Get current and neighbor cells info
	- Print the information
	- Flash the led on pin 13
*/
void loop() {

  getCellInfo();  
  delay(loop_delay_ms);
  
}
