#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<stdint.h> 
#include "spi.h"

int main()
{	
	SPIInit();
	eeprom_chip_erase();
	
}


