#pragma once

// Flash chip: N25Q128A13EF840E

#include <stdio.h>
#include "quadspi.h"

/* Configuration */
#define FLASH_EXT_SIZE               	   		0x2000000 /* 256 MBits*/
#define FLASH_EXT_SECTOR_SIZE              	   	0x10000   /* 64kBytes */
#define FLASH_EXT_PAGE_SIZE                		0x100     /* 256 bytes */

/* Command Definitions */
// Reset operations
#define CMD_RESET_ENABLE 0x66
#define CMD_RESET_MEMORY 0x99
// Identification Operations
#define CMD_READ_ID 0x9E
#define CMD_MULTIPLE_IO_READ_ID 0xAF
#define CMD_READ_SERIAL_FLASH_DISCOVERY_PARAMETER 0x5A
// Read operations
#define CMD_READ 0x03
#define CMD_FAST_READ 0x0B
#define CMD_DUAL_OUTPUT_FAST_READ 0x3B
#define CMD_DUAL_INPUT_OUTPUT_FAST_READ 0xBB
#define CMD_QUAD_OUTPUT_FAST_READ 0x6B
#define CMD_QUAD_INPUT_OUTPUT_FAST_READ 0xEB
// Write operations
#define CMD_WRITE_ENABLE 0x06
#define CMD_WRITE_DISABLE 0x04
// Register operations
#define CMD_READ_STATUS_REGISTER 0x05
#define CMD_WRITE_STATUS_REGISTER 0x01
#define CMD_READ_LOCK_REGISTER 0xE8
#define CMD_WRITE_LOCK_REGISTER 0xE5
#define CMD_READ_FLAG_STATUS_REGISTER 0x70
#define CMD_CLEAR_FLAG_STATUS_REGISTER 0x50
#define CMD_READ_NONVOLATILE_CONFIGURATION_REGISTER 0xB5
#define CMD_WRITE_NONVOLATILE_CONFIGURATION_REGISTER 0xB1
#define CMD_READ_VOLATILE_CONFIGURATION_REGISTER 0x85
#define CMD_WRITE_VOLATILE_CONFIGURATION_REGISTER 0x81
#define CMD_READ_ENHANCED_VOLATILE_CONFIGURATION_REGISTER 0x65
#define CMD_WRITE_ENHANCED_VOLATILE_CONFIGURATION_REGISTER 0x61
// Program operations
#define CMD_PAGE_PROGRAM 0x02
#define CMD_DUAL_INPUT_FAST_PROGRAM 0xA2
#define CMD_EXTENDED_DUAL_INPUT_FAST_PROGRAM 0xD2
#define CMD_QUAD_INPUT_FAST_PROGRAM 0x32
#define CMD_EXTENDED_QUAD_INPUT_FAST_PROGRAM 0x12
// Erase operations
#define CMD_SUBSECTOR_ERASE 0x20
#define CMD_SECTOR_ERASE 0xD8
#define CMD_BULK_ERASE 0xC7
#define CMD_PROGRAM_ERASE_RESUME 0x7A
#define CMD_PROGRAM_ERASE_SUSPEND 0x75
// One-time programmable (OTP) operations
#define CMD_READ_OTP_ARRAY 0x4B
#define CMD_PROGRAM_OTP_ARRAY 0x42

/**
 * \brief Wysyła za pomocą USART odczytaną konfigurację zewnętrznej pamięci flash
 */
void flash_print_info();

/**
 * \brief Wysyła za pomocą USART odczytane z zewnętrznej pamięci flash: kod producenta, typ pamięci, rozmiar pamięci
 */
void flash_print_id();

/**
 * \brief Wysyła za pomocą USART odczytaną z zewnętrznej pamięci flash konfigurację rejestru stanu
 */
void flash_print_status_register();

/**
 * \brief Wysyła za pomocą USART odczytaną z zewnętrznej pamięci flash konfigurację nieulotnego rejestru konfiguracyjnego
 */
void flash_print_nonvolatile_configuration_register();

/**
 * \brief Wysyła za pomocą USART odczytaną z zewnętrznej pamięci flash konfigurację ulotnego rejestru konfiguracyjnego
 */
void flash_print_volatile_configuration_register();

/**
 * \brief Wysyła za pomocą USART odczytaną z zewnętrznej pamięci flash konfigurację ulotnego rejestru konfiguracyjnego (enhanced)
 */
void flash_print_enhanced_volatile_configuration_register();

/**
 * \brief Wysyła za pomocą USART odczytaną z zewnętrznej pamięci flash konfigurację rejestru flag
 */
void flash_print_flag_status_register();

/**
 * \brief Wstrzymuje pracę programu do czasu zakończenia zapisu do zewnętrznej pamięci flash
 *
 * \return Zwraca HAL_OK, jeśli operacja się powiodła lub HAL_ERROR jeśli nie.
 */
uint8_t flash_wait_for_ready();

/**
 * \brief Załącza tryb zapisu zewnętrznej pamięci flash
 *
 * \return Zwraca HAL_OK, jeśli operacja się powiodła lub HAL_ERROR jeśli nie.
 */
uint8_t flash_write_enable();

/**
 * \brief Zapisuje dane z bufora o danej długości w zewnętrznej pamięci flash zaczynając od danego adresu
 *
 * @param start_address - adres pierwszej komórki obszaru, do którego mają zostać zapisane dane
 * @param buffer - wskaźnik na bufor z danymi do zapisu
 * @param buffer_size - wielkość bufora
 *
 * \return Zwraca HAL_OK, jeśli operacja się powiodła lub HAL_ERROR jeśli nie.
 */
uint8_t flash_write(uint32_t start_address, uint8_t *buffer, uint32_t buffer_size);

/**
 * \brief Odczytuje zestaw danch o zadanej długości z zewnętrznej pamięci flash zaczynając od danego adresu do bufora
 *
 * @param start_address - adres pierwszej komórki obszaru, z którego mają zostać odczytane dane
 * @param buffer - wskaźnik na bufor na odczytane dane
 * @param buffer_size - wielkość obaszaru danych do odczytu
 *
 * \return Zwraca HAL_OK, jeśli operacja się powiodła lub HAL_ERROR jeśli nie.
 */
uint8_t flash_read(uint32_t start_address, uint8_t *buffer, uint32_t buffer_size);

/**
 * \brief Funkcja do testowania operacji odczytu/zapisu do/z zewnętrznej pamięci flash
 *
 * Zapisuje bufor danych do zewnętrznej pamięci flash, później odczytuje zapisane dane, porównuje z danymi początkowymi i wysyła za pomocą USART wynik testu.
 */
void flash_test_read_write();




