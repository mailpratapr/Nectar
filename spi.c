#include "spi.h"


/**
 * Set CS to low
 */
void low_cs()
{
	//set cs to low
}


/**
 * Set CS to high
 */
void high_cs()
{
	//set cs to high
}


/**
 * Initializes SPI
 * Configures CLK, MISO, MOSI pins and CLK speed
 */
void SPIInit(void)
{
	//lpc_pconp(pconp_ssp0, true); Turn on the peripheral
    //lpc_pclk(pclk_ssp0, clkdiv_1); Set the clock divider
    //Set the 8 bit mode
    //Set as master
    
}


/**
 * Write a byte in SPI Serial EEPROM
 * @param address   The address in SPI Serial EEPROM
 * @param data      The byte to SPI Serial EEPROM
 */
void write_byte(uint32_t address, uint8_t data)
{
	low_cs();  
	 
	SPI_Mems_Write_Reg(0x06);  //Opcode for WREN
	send_address(address);     //Destination address 
    SPI_Mems_Write_Reg(data);  //Data
    
    high_cs();
}


/**
 * Read a byte from SPI Serial EEPROM
 * @param address   The address in SPI Serial EEPROM
 * @returns         The byte from SPI Serial EEPROM
 */
uint8_t read_byte(uint32_t address)
{
	uint8_t data;
	low_cs();
	
	SPI_Mems_Write_Reg(0x04);  //Opcode for WRDI
	send_address(address);     //Address 
	data=SPI_Mems_Read_Reg(0); //Read data
	high_cs();
	
	return data;
}



/**
 * Write a page to SPI Serial EEPROM
 * @param address   The starting address in SPI Serial EEPROM
 */
void write_page(uint32_t address, uint8_t *data)
{
	uint8_t addbits;
	uint32_t next_addbits,mask = 0x000000FF;;
	int pos = (int)(mask & address);
	int bytes=256-pos;          //Determine current position in the page
	int i=0;

	low_cs();
	
	SPI_Mems_Write_Reg(0x06);   //Opcode for WREN
	send_address(address);      //Starting destination address for page write
	
	for(i;i<bytes;++i)
	{
		SPI_Mems_Write_Reg(*data++);  //Start writing data from the current position 
	}
	
	high_cs();
	next_addbits = (uint32_t)(mask & (address >> 8));  

	if((pos!=0) && (next_addbits!=0x1FF))   //If the starting position is not zero and next page address does not cross the maximum
	{
		next_addbits=next_addbits+1;
		next_addbits=next_addbits<<8;       //Next page address

		low_cs();                           
		SPI_Mems_Write_Reg(0x06);           //Opcode for WREN
		send_address(next_addbits);         //Destination address for the remaining data
	
	    for(i;i<=pos;++i)
	      {
		    SPI_Mems_Write_Reg(*data++);    //Reamining data to be written
	      }
	      
	    high_cs();
	}
}


/**
 * Read a page from SPI Serial EEPROM
 * @param address   The starting address in SPI Serial EEPROM
 */
int read_page(uint32_t address, uint8_t *data)
{
	int i=0;
	
	low_cs();
	 
	SPI_Mems_Write_Reg(0x04);               //Opcode for WRDI
	send_address(address);                  //Starting address for reading page 
	
	for(i;i<=255;++i)
	{
		*data++ = SPI_Mems_Read_Reg(0);     //Reading data
	}

	high_cs();
	
	return 0;
}


/**
 * Erase the entire SPI Serial EEPROM
 */
void eeprom_chip_erase(void)
{
	uint32_t max=0x1FF00, i=0;
	
	low_cs();
	
	for(i=0;i<=max;i+=0x100)
	{
		write_page(i,0x00);                //Start erasing page by page
	}
	
	high_cs();
}


/**
 * Write address in SPI Serial BUS
 * @param address   The address in Serial EEPROM
 */
void send_address(uint32_t address)
{
	uint8_t addbits;
	uint32_t mask = 0x000000FF;           //Mask to get 8 bit address for serail transfer
	
	addbits = (uint8_t)(mask & (address >> 16));  //MSB 8 bits from address
	SPI_Mems_Write_Reg(addbits);
	
	addbits = (uint8_t)(mask & (address >> 8));   //Bits 8 to 15 from address 
	SPI_Mems_Write_Reg(addbits);
	
	addbits = (uint8_t)(mask & address);           //LSB 8 bits from address
	SPI_Mems_Write_Reg(addbits);
}


/**
 * Write SPI TX data to register
 * @param tx_data   The data to to written in SPI bus
 */
void SPI_Mems_Write_Reg(uint8_t tx_data)
{
	return;
}


/**
 * Read SPI RX data from register
 * @returns   The data read from SPI bus
 */
uint8_t SPI_Mems_Read_Reg(uint8_t rx_data)
{
	uint8_t rdata;
	return rdata;
}
