#include "LTask.h"
#include "vmcell.h"
#include <LGPRS.h>


// Cellular Network information refresh delay
const int loop_delay_ms = 5000;

/* 
	Wrapper to the low-level function vm_cell_open()
	Initialize the Cell register on LinkIt ONE
*/
static boolean cell_open(void *userData) {
  *(VMINT *)userData = vm_cell_open();
  return TRUE;
}


/*
	Wrapper to the low-level function vm_cell_get_cur_cell_info()
	Get the current cell info. Result is stored into a struct
*/
static boolean get_current_cell_info(void *userData) {
  *(vm_cell_info_struct **)userData = vm_cell_get_cur_cell_info();
  return TRUE;
}

/*
	Wrapper to the low-level function vm_cell_get_nbr_num()
	Get the number of neighbor cells
*/
static boolean get_neighbor_cell_number(void *userData) {
  *(VMINT **)userData = vm_cell_get_nbr_num();
  return TRUE;
}

/*
	Wrapper to the low-level function vm_cell_get_nbr_cell_info()
	Get the neighbor cells info. Result is stored into a struct array
*/
static boolean get_neighbor_cell_info(void *userData) {
 *(vm_cell_info_struct***) userData = vm_cell_get_nbr_cell_info();
 return TRUE;
}


void init_cell_register() {
  VMINT cell_open_result;
  boolean stop = FALSE;
  
  Serial.print("Initializing...  ");
  LTask.remoteCall(&cell_open, (void *)&cell_open_result);
  
  while(!stop) {
    switch(cell_open_result) {
      case VM_CELL_OPEN_SUCCESS:
      Serial.println("Done.");
      stop = TRUE;
      break;

      case VM_CELL_OPEN_ALREADY_OPEN:
      Serial.println("Done. Cell register was already open.");
      stop = TRUE;
      break;

      case VM_CELL_OPEN_RES_LESS:
      Serial.println("Error. Lack of resources while opening cell register. Retrying in 5 seconds.");
      delay(5000);      
      break;

      case VM_CELL_OPEN_REG_ERROR:
      Serial.println("Error while opening cell register. Retrying in 5 seconds.");
      delay(5000);      
      break;

      default:
      Serial.println("Unknown error while opening cell register. Retrying in 5 seconds.");
      delay(5000);
      
    }
  }
}




void print_cell_info(vm_cell_info_struct* cell_ptr) {
  if (cell_ptr == NULL) {
    Serial.println("No cell info available");
  }
  else {
    Serial.print(" MCC:");
    Serial.print(cell_ptr->mcc);
    Serial.print(" MNC:");
    Serial.print(cell_ptr->mnc);
    Serial.print(" BSIC:");
    Serial.print(cell_ptr->bsic);
    Serial.print(" LAC:");
    Serial.print(cell_ptr->lac);
    Serial.print(" Cell ID:");
    Serial.print(cell_ptr->ci);
    Serial.print(" ARFCN:");
    Serial.print(cell_ptr->arfcn);
    Serial.print(" Signal level:");
    Serial.println(cell_ptr->rxlev);
  }
}


void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  while(!Serial) {
    delay(250);
  }
  
  init_cell_register();
 }

/*
	- Get current and neighbor cells info
	- Print the information
	- Flash the led on pin 13
*/
void loop() {

  attachGPRS(apn1, user1, pass1) ;

  VMINT *neighbor_cell_number;
  vm_cell_info_struct *current_cell_ptr;
  vm_cell_info_struct **neighbor_cell_ptr;

  digitalWrite(13, HIGH);

  // Get current and neighbor cells info
  LTask.remoteCall(&get_current_cell_info, (void *)&current_cell_ptr);
  LTask.remoteCall(&get_neighbor_cell_number, (void *)&neighbor_cell_number);
  LTask.remoteCall(&get_neighbor_cell_info, (void *)&neighbor_cell_ptr);


  Serial.print("Current cell info    :");
  print_cell_info(current_cell_ptr);
  
  if (neighbor_cell_number != NULL){
    if (*neighbor_cell_number > 0) {
      for (int i = 0; i < *neighbor_cell_number; i++) {    
        Serial.print("Neighbor cell #");Serial.print(i); Serial.print(" info:");
        print_cell_info(neighbor_cell_ptr[i]);
      }
    }
  }
  else {
    Serial.println("Unable to get number of neighbor cells");
  }
  Serial.println();
  
  delay(loop_delay_ms);  
  digitalWrite(13, LOW);
  }
