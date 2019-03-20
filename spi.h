#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<stdint.h> 

void SPI_Mems_Write_Reg(uint8_t tx_data); 
uint8_t SPI_Mems_Read_Reg(uint8_t rx_data); 
void SPIInit(void);

void write_byte(uint32_t address, uint8_t data); // write one byte of data into the address specified 
void write_page(uint32_t address, uint8_t *data); // write one page of data into the address specified 
uint8_t read_byte(uint32_t address); // read one byte of data from the address specified 
int read_page(uint32_t address, uint8_t *data); // read one page of data from the address specified 
void eeprom_chip_erase(void); //erase the entire chip
void send_address(uint32_t address); //Write address in SPI Serial BUS as bytes


void low_cs();
void high_cs();
