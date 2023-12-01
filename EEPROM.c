/*
 * EEPROM.c
 *
 * Created: 15-11-23 11:39:52
 *  Author: flori
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "USART.h"
#include "EEPROM.h"
#include "I2C_Master.h"


unsigned char EEPROM_buf[I2C_BUFFER_SIZE];
extern unsigned char TWI_buf[I2C_BUFFER_SIZE];


unsigned char Eeprom_Read(uint16_t address) {
	EEPROM_buf[0] = ((EEPROM_ADDRESS<<1)|0);		//Salve Address + W
	EEPROM_buf[1]=(unsigned char)((address >> 8) & 0xFF);
	EEPROM_buf[2]=(unsigned char)(address & 0xFF);
	TWI_Start_Transceiver_With_Data(EEPROM_buf, 3);
	EEPROM_buf[0] = ((EEPROM_ADDRESS<<1)|1);		//Salve Address + R
	TWI_Start_Transceiver_With_Data(EEPROM_buf, 2);
	while ( TWI_Transceiver_Busy() );
	// Wait until TWI is ready for next transmission.
	// FOR DEBUG
	//Usart0_Tx(TWI_buf[1]);
	//Usart0_Tx_String("inside read");/*

	return TWI_buf[1];
}

void EEPROM_Write(unsigned int ad,unsigned int nbr_byte,char msg[]){
	int buffersize=nbr_byte+3;
	unsigned char EEPROM_BUFF_2[buffersize];
	EEPROM_BUFF_2[0]=((EEPROM_ADDRESS<<1)|0);
	EEPROM_BUFF_2[1]=(unsigned char)((ad >> 8) & 0xFF);
	EEPROM_BUFF_2[2]=(unsigned char)(ad & 0xFF);
	for(int i = 0;i<nbr_byte;i++){
		EEPROM_BUFF_2[i+3]=msg[i];
	}
	TWI_Start_Transceiver_With_Data(EEPROM_BUFF_2,buffersize);
}
void EEPROM_Write_String(const char* word, unsigned int ad){
	unsigned int Nbr_byte=strlen(word);
	Usart0_Tx(Nbr_byte);
	EEPROM_Write(ad,Nbr_byte,word);
}

