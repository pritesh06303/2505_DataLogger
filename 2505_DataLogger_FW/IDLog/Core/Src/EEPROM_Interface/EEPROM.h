/*
 * EEPROM.h
 *
 *  Created on: Nov 1, 2025
 *      Author: TITHI
 */

#ifndef EEPROM_INTERFACE_EEPROM_H_
#define EEPROM_INTERFACE_EEPROM_H_


#define EEPROM_CS_LOW()   HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_RESET)
#define EEPROM_CS_HIGH()  HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_SET)


// ===== EEPROM Instructions =====
#define EEPROM_WREN   			0x06
#define EEPROM_WRDI   			0x04
#define EEPROM_RDSR   			0x05
#define EEPROM_WRSR   			0x01
#define EEPROM_READ   			0x03
#define EEPROM_WRITE  			0x02
#define EEPROM_PAGE_ERASE       0xDB
#define EEPROM_SECTOR_ERASE     0x20
#define EEPROM_BLOCK_ERASE      0xD8
#define EEPROM_CHIP_ERASE       0xC7

// ===== EEPROM Specs =====
#define EEPROM_PAGE_SIZE        512     // 512 bytes per page
#define EEPROM_NUM_PAGES        2048    // 2048 pages total
#define EEPROM_MEMORY_SIZE      (EEPROM_PAGE_SIZE * EEPROM_NUM_PAGES)


// ===== Function Prototypes =====
void EEPROM_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *csPort, uint16_t csPin);

uint8_t EEPROM_ReadStatus(void);
void EEPROM_WriteEnable(void);

void EEPROM_WriteByte(uint32_t addr, uint8_t data);
uint8_t EEPROM_ReadByte(uint32_t addr);

void EEPROM_WritePage(uint32_t addr, uint8_t *buffer, uint16_t len);
void EEPROM_ReadData(uint32_t addr, uint8_t *buffer, uint16_t len);

void EEPROM_ErasePage(uint32_t page_address);
void EEPROM_EraseSector(uint32_t sector_address);
void EEPROM_EraseChip();



#endif /* EEPROM_INTERFACE_EEPROM_H_ */
