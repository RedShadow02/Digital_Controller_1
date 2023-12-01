/*
 * EEPROM_24LC1025.h
 *
 * Created: 01-12-23 10:19:46
 *  Author: flori
 */ 


#ifndef EEPROM_24LC1025_H_
#define EEPROM_24LC1025_H_
#define EEPROM_ADDRESS 0b1010000 // The I2C address for the 24LC1025
#define I2C_BUFFER_SIZE  4

unsigned char Eeprom_Read(uint16_t address);
void EEPROM_Write(unsigned int ad,unsigned int nbr_byte,char msg[]);
void EEPROM_Write_String(  char *word, unsigned int ad);





#endif /* EEPROM_24LC1025_H_ */