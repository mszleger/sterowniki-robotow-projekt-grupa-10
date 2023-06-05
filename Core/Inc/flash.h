#pragma once

// ----- SETTINGS ----- //
#define TRACK_AMOUNT            8
#define SUBSECTORS_PER_TRACK    511

//#define FLASH_DEBUG_VERBOSE

// Flash chip: N25Q128A13EF840E

#include "stdio.h"
#include "string.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_qspi.h"

#define TRACK_STATUS_SUBSECTOR 1
#define SUBSECTOR_SIZE      4096

#define TRACK_EMPTY 0
#define TRACK_SAVED 1

QSPI_Info flash_info;

uint32_t track_status_page_start_address;
uint8_t  track_status_value[TRACK_AMOUNT];

uint32_t track_begin_address[TRACK_AMOUNT];

uint32_t record_address;
uint32_t record_end_address; // start address of next track

uint32_t play_address;
uint32_t play_end_address; // start address of next track


/* ---------- USER INTERFACE ---------- */
HAL_StatusTypeDef Flash_Init(void);

HAL_StatusTypeDef Flash_Track_Status_Set(uint8_t track_number, uint8_t  track_status);
HAL_StatusTypeDef Flash_Track_Status_Get(uint8_t track_number, uint8_t* track_status);

HAL_StatusTypeDef Flash_Track_Record_Start(uint8_t track_number);
uint32_t Flash_Track_Record_Buffer_Save(uint8_t* buffer, uint32_t buffer_length);

HAL_StatusTypeDef Flash_Track_Play_Start(uint8_t track_number);
uint32_t Flash_Track_Play_Buffer_Read(uint8_t* buffer, uint32_t buffer_length);

HAL_StatusTypeDef Flash_Test(void);
