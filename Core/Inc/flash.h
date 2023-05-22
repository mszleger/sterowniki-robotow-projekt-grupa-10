#pragma once

// Flash chip: N25Q128A13EF840E

#include "stdio.h"
#include "string.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_qspi.h"



#define BUFFER_SIZE         ((uint32_t)0x0200)
#define WRITE_READ_ADDR     ((uint32_t)0x0050)
#define QSPI_BASE_ADDR      ((uint32_t)0x90000000)

uint8_t qspi_aTxBuffer[BUFFER_SIZE];
uint8_t qspi_aRxBuffer[BUFFER_SIZE];





void QSPI_demo(void);



/**
 *
 */
HAL_StatusTypeDef Flash_Init(void);

/**
 *
 */
HAL_StatusTypeDef Flash_Test(void);

/**
 *
 */
HAL_StatusTypeDef Flash_Read(uint32_t start_address, uint8_t* buffer, uint32_t buffer_length);

/**
 *
 */
HAL_StatusTypeDef Flash_Write(uint32_t start_address, uint8_t* buffer, uint32_t buffer_length);


/**
 *
 */
HAL_StatusTypeDef Flash_Track_Status_Set(uint8_t track_number, uint8_t new_track_status);

/**
 *
 */
HAL_StatusTypeDef Flash_Track_Status_Get(uint8_t track_number, uint8_t* track_status);

/**
 *
 */
HAL_StatusTypeDef Flash_Record_Start(uint8_t track_number);

/**
 *
 */
HAL_StatusTypeDef Flash_Record_Save_Buffer(uint8_t* buffer, uint32_t buffer_length);

/**
 *
 */
HAL_StatusTypeDef Flash_Play_Start(uint8_t track_number);

/**
 *
 */
HAL_StatusTypeDef Flash_Play_Read_Buffer(uint8_t* buffer, uint32_t buffer_length);













