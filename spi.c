#include "spi.h"

void low_cs()
{
	//set cs to low
}

void high_cs()
{
	//set cs to high
}

void SPIInit(void)
{
	//lpc_pconp(pconp_ssp0, true); Turn on the peripheral
    //lpc_pclk(pclk_ssp0, clkdiv_1); Set the clock divider
    //Set the 8 bit mode
    //Set as master
    
}

void write_byte(uint32_t address, uint8_t data)
{
	uint8_t addbits;
	uint32_t mask = 0x000000FF;
	
	low_cs();
	
	SPI_Mems_Write_Reg(0x06);

	addbits = (uint8_t)(mask & (address >> 16));
	SPI_Mems_Write_Reg(addbits);
	
	addbits = (uint8_t)(mask & (address >> 8));
	SPI_Mems_Write_Reg(addbits);
	
	addbits = (uint8_t)(mask & address);
	SPI_Mems_Write_Reg(addbits);
	
    SPI_Mems_Write_Reg(data);
    
    high_cs();
}

uint8_t read_byte(uint32_t address)
{
	uint8_t addbits,data;
	uint32_t mask = 0x000000FF;
	
	low_cs();
	
	SPI_Mems_Write_Reg(0x04);
	
	addbits = (uint8_t)(mask & (address >> 16));
	SPI_Mems_Write_Reg(addbits);
	
	addbits = (uint8_t)(mask & (address >> 8));
	SPI_Mems_Write_Reg(addbits);
	
	addbits = (uint8_t)(mask & address);
	SPI_Mems_Write_Reg(addbits);
	
	data=SPI_Mems_Read_Reg(0);
	
	high_cs();
	
	return data;
}

void write_page(uint32_t address, uint8_t *data)
{
	uint8_t addbits;
	uint32_t mask = 0x000000FF;
	uint32_t next_addbits;
	
	int pos = (int)(mask & address);
	int bytes=256-pos;
	int i=0;
	
	low_cs();
	
	SPI_Mems_Write_Reg(0x06);
	
	addbits = (uint8_t)(mask & (address >> 16));
	SPI_Mems_Write_Reg(addbits);
	
	addbits = (uint8_t)(mask & (address >> 8));
	SPI_Mems_Write_Reg(addbits);
	
	addbits = (uint8_t)(mask & address);
	SPI_Mems_Write_Reg(addbits);
	
	for(i;i<bytes;++i)
	{
		SPI_Mems_Write_Reg(*data++);
	}
	
	high_cs();
	
	next_addbits = (uint32_t)(mask & (address >> 8));
	if((pos!=0) && (next_addbits!=0x1FF))
	{
		next_addbits=next_addbits+1;
		
		low_cs();
		SPI_Mems_Write_Reg(0x06);
	
	    addbits = (uint8_t)(mask & (next_addbits >> 8));
	    SPI_Mems_Write_Reg(addbits);
	
	    addbits = (uint8_t)(mask & (next_addbits));
	    SPI_Mems_Write_Reg(addbits);
	
	    addbits = (uint8_t)(0x00);
	    SPI_Mems_Write_Reg(addbits);
	    
	    for(i;i<=pos;++i)
	      {
		    SPI_Mems_Write_Reg(*data++);
	      }
	      
	    high_cs();
	}
}

int read_page(uint32_t address, uint8_t *data)
{
	uint8_t addbits;
	uint32_t mask = 0x000000FF;
	int i=0;
	
	low_cs();
	
	SPI_Mems_Write_Reg(0x04);
	
	addbits = (uint8_t)(mask & (address >> 16));
	SPI_Mems_Write_Reg(addbits);
	
	addbits = (uint8_t)(mask & (address >> 8));
	SPI_Mems_Write_Reg(addbits);
	
	addbits = (uint8_t)(mask & address);
	SPI_Mems_Write_Reg(addbits);
	
	for(i;i<=255;++i)
	{
		*data++ = SPI_Mems_Read_Reg(0);
	}
	
	high_cs();
	
	return 0;
}

void eeprom_chip_erase(void)
{
	uint32_t i=0;
	uint32_t max=0x1FF;
	
	low_cs();
	
	for(i=0;i<=max;++i)
	{
		write_page(i,0x00);
	}
	
	high_cs();
}

void SPI_Mems_Write_Reg(uint8_t tx_data)
{
	return;
}

uint8_t SPI_Mems_Read_Reg(uint8_t rx_data)
{
	uint8_t rdata;
	return rdata;
}

