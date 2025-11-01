/*
 * EEPROM.c
 *
 *  Created on: Nov 1, 2025
 *      Author: TITHI
 */

#include "HardwareConfig.h"



// ===== Init Function =====
//void EEPROM_Init(SPI_HandleTypeDef *hspi, GPIO_TypeDef *csPort, uint16_t csPin) {
//    EEPROM_SPI = hspi;
//    EEPROM_CS_PORT = csPort;
//    EEPROM_CS_PIN = csPin;
//    EEPROM_CS_HIGH();
//}

// --- Send 1 byte over SPI ---
uint8_t SPI_TxRx(uint8_t data) {
    uint8_t rx;
    HAL_SPI_TransmitReceive(&hspi3, &data, &rx, 1, HAL_MAX_DELAY);
    return rx;
}

// --- Write Enable ---
void EEPROM_WriteEnable(void) {
    EEPROM_CS_LOW();
    SPI_TxRx(EEPROM_WREN);
    EEPROM_CS_HIGH();
}

// --- Read Status Register ---
uint8_t EEPROM_ReadStatus(void) {
    uint8_t status;
    EEPROM_CS_LOW();
    SPI_TxRx(EEPROM_RDSR);
    status = SPI_TxRx(0xFF);
    EEPROM_CS_HIGH();
    return status;
}

// ===== Wait Until Ready (WIP=0) =====
static void EEPROM_WaitReady(void) {
    while (EEPROM_ReadStatus() & 0x01); // WIP bit
}

// --- Write one byte ---
void EEPROM_WriteByte(uint32_t addr, uint8_t data) {
    EEPROM_WriteEnable();

    EEPROM_CS_LOW();
    SPI_TxRx(EEPROM_WRITE);
    SPI_TxRx((addr >> 16) & 0xFF); // 3-byte address
    SPI_TxRx((addr >> 8) & 0xFF);
    SPI_TxRx(addr & 0xFF);
    SPI_TxRx(data);
    EEPROM_CS_HIGH();

    // Wait until write complete (WIP=0 in status register)
    EEPROM_WaitReady();
}

// --- Read one byte ---
uint8_t EEPROM_ReadByte(uint32_t addr) {
    uint8_t data;
    EEPROM_CS_LOW();
    SPI_TxRx(EEPROM_READ);
    SPI_TxRx((addr >> 16) & 0xFF);
    SPI_TxRx((addr >> 8) & 0xFF);
    SPI_TxRx(addr & 0xFF);
    data = SPI_TxRx(0xFF);
    EEPROM_CS_HIGH();
    return data;
}



// ===== Page Write (up to 256 bytes) =====
void EEPROM_WritePage(uint32_t addr, uint8_t *buffer, uint16_t len)
{
    if (len > EEPROM_PAGE_SIZE) len = EEPROM_PAGE_SIZE;

    EEPROM_WriteEnable();

    EEPROM_CS_LOW();
    SPI_TxRx(EEPROM_WRITE);
    SPI_TxRx((addr >> 16) & 0xFF);
    SPI_TxRx((addr >> 8) & 0xFF);
    SPI_TxRx(addr & 0xFF);

    HAL_SPI_Transmit(&hspi3, buffer, len, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();

    // Wait until write complete (WIP=0 in status register)
    EEPROM_WaitReady();
}



// ===== Read Multiple Bytes =====
void EEPROM_ReadData(uint32_t addr, uint8_t *buffer, uint16_t len)
{
    EEPROM_CS_LOW();
    SPI_TxRx(EEPROM_READ);
    SPI_TxRx((addr >> 16) & 0xFF);
    SPI_TxRx((addr >> 8) & 0xFF);
    SPI_TxRx(addr & 0xFF);

    HAL_SPI_Receive(&hspi3, buffer, len, HAL_MAX_DELAY);
    EEPROM_CS_HIGH();
}


/**
 * @brief Erases a single 512-byte page.
 * @param page_address The base address of the page to erase.
 */
void EEPROM_ErasePage(uint32_t page_address)
{
    EEPROM_WriteEnable();

    EEPROM_CS_LOW();
    SPI_TxRx(EEPROM_PAGE_ERASE);
    SPI_TxRx((page_address >> 16) & 0xFF);
    SPI_TxRx((page_address >> 8) & 0xFF);
    SPI_TxRx(page_address & 0xFF);

    EEPROM_CS_HIGH();

    // Wait until write complete (WIP=0 in status register)
    EEPROM_WaitReady();
}

