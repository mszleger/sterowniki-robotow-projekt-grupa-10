#pragma once

// ----- SETTINGS ----- //
#define TRACK_AMOUNT            5
#define TRACK_SPACE_LENGTH      ((uint32_t)0x0200)
#define USER_DATA_BEGIN_ADDRESS ((uint32_t)0x0050)

// Flash chip: N25Q128A13EF840E

#include "stdio.h"
#include "string.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_qspi.h"

QSPI_Info flash_info;
uint32_t track_status_address[TRACK_AMOUNT];
uint32_t track_begin_address[TRACK_AMOUNT];

uint32_t record_address;
uint32_t record_end_address; // start address of next track

uint32_t play_address;
uint32_t play_end_address; // start address of next track

/**
 *
 */
HAL_StatusTypeDef Flash_Init(void);

/**
 *
 */
HAL_StatusTypeDef Flash_Init_Tracks_Layout(void);

/**
 *
 */
HAL_StatusTypeDef Flash_Test(void);



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
uint32_t Flash_Record_Save_Buffer(uint8_t* buffer, uint32_t buffer_length);

/**
 *
 */
HAL_StatusTypeDef Flash_Play_Start(uint8_t track_number);

/**
 *
 */
uint32_t Flash_Play_Read_Buffer(uint8_t* buffer, uint32_t buffer_length);













