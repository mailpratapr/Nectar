#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<stdint.h> 
#include "spi.h"

void main() {
  uint8_t data;
  uint8_t tx[256] = {
    0x05
  };
  uint8_t rx[256] = {
    0x00
  };
  SPIInit();
  eeprom_chip_erase(); //Erase chip

  write_byte(0xA0, 0x05); //Write one byte
  data = read_byte(0xAA); //Read one byte

  write_page(0xA00, tx); //Write one page data
  read_page(0xA00, rx); //Read one page

  printf("Done");
}
