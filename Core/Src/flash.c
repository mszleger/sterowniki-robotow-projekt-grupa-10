#include "flash.h"

static HAL_StatusTypeDef Flash_Track_Load_Statuses() {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Track_Load_Statuses\r\n");
	#endif
	return BSP_QSPI_Read(track_status_value, track_status_page_start_address, TRACK_AMOUNT);
}

static HAL_StatusTypeDef Flash_Init_Tracks_Layout(void) {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Init_Tracks_Layout\r\n");
	#endif
	HAL_StatusTypeDef status;
	if((TRACK_STATUS_SUBSECTOR + (TRACK_AMOUNT * SUBSECTORS_PER_TRACK)) * SUBSECTOR_SIZE > flash_info.FlashSize) {
		printf("     - Not enough space for given track amount and size\r\n");
		return HAL_ERROR;
	}
	track_status_page_start_address = 0;
	track_begin_address[0] = (TRACK_STATUS_SUBSECTOR) * SUBSECTOR_SIZE;
	for(uint8_t i = 1; i < TRACK_AMOUNT; ++i) {
		track_begin_address[i] = track_begin_address[i - 1] + (SUBSECTORS_PER_TRACK * SUBSECTOR_SIZE);
		#ifdef FLASH_DEBUG_VERBOSE
			printf("     - Track %d begin address: %ld\r\n", i, track_begin_address[i]);
		#endif
	}
	status = Flash_Track_Load_Statuses();
	if(status != HAL_OK) {
		printf("     - Failed to load tracks' statuses\r\n");
		return status;
	}
	return HAL_OK;
}

static HAL_StatusTypeDef Flash_Test_All_Tracks_Statuses() {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Test_All_Tracks_Statuses\r\n");
	#endif
	HAL_StatusTypeDef status;
	uint8_t buffer;
	uint8_t test_values[2] = {0x00, 0xff};
	uint8_t test_values_amount = 2;
	for(uint8_t test_value_id = 0; test_value_id < test_values_amount; ++test_value_id) {
		for(uint8_t track_status_id = 0; track_status_id < TRACK_AMOUNT; ++track_status_id) {
			status = Flash_Track_Status_Set(track_status_id, test_values[test_value_id]);
			if(status != HAL_OK) {
				printf("     - Failed to set status of track %d\r\n", track_status_id);
				return status;
			}
			status = Flash_Track_Status_Get(track_status_id, &buffer);
			if(status != HAL_OK) {
				printf("     - Failed to read status of track %d\r\n", track_status_id);
				return status;
			}
			if(buffer != test_values[test_value_id]) {
				printf("     - Test failed: Value of track status %d is equal to %d instead of %d\r\n", track_status_id, buffer, test_values[test_value_id]);
				return HAL_ERROR;
			}
			#ifdef FLASH_DEBUG_VERBOSE
				printf("     - Correct value of track %d status: readed %d; expected %d\r\n", track_status_id, buffer, test_values[test_value_id]);
			#endif
		}
	}
	return HAL_OK;
}

static HAL_StatusTypeDef Flash_Test_Record_And_Play() {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Test_Record_And_Play\r\n");
	#endif
	HAL_StatusTypeDef status;
	uint8_t buffer_tx[256];
	uint8_t buffer_rx[256];
	uint32_t saved_buffers_amount = 0;
	uint32_t correct_readed_buffers_amount = 0;
	for(uint32_t i = 0; i < 256; ++i)
		buffer_tx[i] = i;
	for(uint8_t track_id = 0; track_id < TRACK_AMOUNT; ++track_id) {
		status = Flash_Track_Record_Start(track_id);
		if(status != HAL_OK){
			printf("     - Failed to start recording of track %d\r\n", track_id);
			return status;
		}
		while(Flash_Track_Record_Buffer_Save(buffer_tx, 256) == 256)
			++saved_buffers_amount;
		status = Flash_Track_Play_Start(track_id);
		if(status != HAL_OK) return status;
		while(Flash_Track_Play_Buffer_Read(buffer_rx, 256) == 256) {
			for(uint32_t i = 0; i < 256; ++i) {
				if(buffer_rx[i] != buffer_tx[i]) {
					printf("     - buffer tx and rx not equal at index %ld: rx = %d, tx = %d\r\n", i, buffer_rx[i], buffer_tx[i]);
					--correct_readed_buffers_amount;
					break;
				}
			}
			++correct_readed_buffers_amount;
		}
	}
	#ifdef FLASH_DEBUG_VERBOSE
		printf("     - saved %ld buffers, readed %ld correct buffers\r\n", saved_buffers_amount, correct_readed_buffers_amount);
	#endif
	if(saved_buffers_amount != correct_readed_buffers_amount) {
		printf("     - testing recording and playing failed: saved buffers amount (%ld) != correctly readed buffers amount (%ld)\r\n", saved_buffers_amount, correct_readed_buffers_amount);
		return HAL_ERROR;
	}
	return HAL_OK;
}

HAL_StatusTypeDef Flash_Track_Status_Set(uint8_t track_number, uint8_t new_track_status) {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Track_Status_Set\r\n");
	#endif
	HAL_StatusTypeDef status;
	uint8_t track_status_value_copy[TRACK_AMOUNT];
	if(track_number >= TRACK_AMOUNT) {
		printf("     - Incorrect track number: %d\r\n", track_number);
		return HAL_ERROR;
	}
	for(uint8_t i = 0; i < TRACK_AMOUNT; ++i)
		track_status_value_copy[i] = track_status_value[i];
	track_status_value_copy[track_number] = new_track_status;
	status = BSP_QSPI_Erase_Block(track_status_page_start_address);
	if(status != HAL_OK) {
		printf("     - Failed to erase track status block\r\n");
		return status;
	}
	status = BSP_QSPI_Write(track_status_value_copy, track_status_page_start_address, TRACK_AMOUNT);
	if(status != HAL_OK) {
		printf("     - Failed to save tracks' statuses\r\n");
		return status;
	}
	status = Flash_Track_Load_Statuses();
	if(status != HAL_OK) {
		printf("     - Failed to load tracks' statuses\r\n");
		return status;
	}
	return HAL_OK;
}

HAL_StatusTypeDef Flash_Track_Status_Get(uint8_t track_number, uint8_t* track_status) {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Track_Status_Get\r\n");
	#endif
	if(track_number >= TRACK_AMOUNT) {
		printf("     - Incorrect track number: %d\r\n", track_number);
		return HAL_ERROR;
	}
	*track_status = track_status_value[track_number];
	return HAL_OK;
}

HAL_StatusTypeDef Flash_Track_Record_Start(uint8_t track_number) {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Record_Start\r\n");
	#endif
	HAL_StatusTypeDef status;
	if(track_number >= TRACK_AMOUNT) {
		printf("     - Incorrect track number: %d\r\n", track_number);
		return HAL_ERROR;
	}
	record_address = track_begin_address[track_number];
	record_end_address = track_begin_address[track_number] + (SUBSECTORS_PER_TRACK * SUBSECTOR_SIZE);
	for(uint32_t i = 0; i < SUBSECTORS_PER_TRACK; ++i) {
		status = BSP_QSPI_Erase_Block(track_begin_address[track_number] + (i * SUBSECTOR_SIZE));
		if(status != HAL_OK) {
			printf("     - Failed to erase sector: %ld\r\n", track_begin_address[track_number] + (i * SUBSECTOR_SIZE));
			return status;
		}
	}
	return HAL_OK;
}

uint32_t Flash_Track_Record_Buffer_Save(uint8_t* buffer, uint32_t buffer_length) {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Record_Save_Buffer\r\n");
	#endif
	if(buffer_length > record_end_address - record_address)
		buffer_length = record_end_address - record_address;
	if(buffer_length == 0) return 0;
	if(BSP_QSPI_Write(buffer, record_address, buffer_length) != HAL_OK) {
		printf("     - Failed to write track to flash\r\n");
		return 0;
	}
	record_address += buffer_length;
	return buffer_length;
}

HAL_StatusTypeDef Flash_Track_Play_Start(uint8_t track_number) {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Play_Start\r\n");
	#endif
	if(track_number >= TRACK_AMOUNT) {
		printf("     - Incorrect track number: %d\r\n", track_number);
		return HAL_ERROR;
	}
	play_address = track_begin_address[track_number];
	play_end_address = track_begin_address[track_number] + (SUBSECTORS_PER_TRACK * SUBSECTOR_SIZE);
	return HAL_OK;
}

uint32_t Flash_Track_Play_Buffer_Read(uint8_t* buffer, uint32_t buffer_length) {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Play_Read_Buffer\r\n");
	#endif
	if(buffer_length > play_end_address - play_address)
		buffer_length = play_end_address - play_address;
	if(buffer_length == 0) return 0;
	if(BSP_QSPI_Read(buffer, play_address, buffer_length) != HAL_OK) {
		printf("     - Failed to read track from flash\r\n");
		return 0;
	}
	play_address += buffer_length;
	return buffer_length;
}

HAL_StatusTypeDef Flash_Test(void) {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Test\r\n");
	#endif
	HAL_StatusTypeDef status;
	status = Flash_Test_All_Tracks_Statuses();
	if(status != HAL_OK) {
		printf("     - Testing all tracks' statuses failed\r\n");
		return status;
	}
	status = Flash_Test_Record_And_Play();
	if(status != HAL_OK) {
		printf("     - Testing recording and playing failed\r\n");
		return status;
	}
	return HAL_OK;
}















HAL_StatusTypeDef Flash_Init(void) {
	#ifdef FLASH_DEBUG_VERBOSE
		printf("FLASH: Flash_Init\r\n");
	#endif
	HAL_StatusTypeDef status;

	status = BSP_QSPI_Init(); // TODO: wyrzucić init BSP
	if(status != HAL_OK) return status;

    flash_info.FlashSize          = (uint32_t)0x00;
    flash_info.EraseSectorSize    = (uint32_t)0x00;
    flash_info.EraseSectorsNumber = (uint32_t)0x00;
    flash_info.ProgPageSize       = (uint32_t)0x00;
    flash_info.ProgPagesNumber    = (uint32_t)0x00;

    BSP_QSPI_GetInfo(&flash_info);

    if((flash_info.FlashSize != 0x1000000)     ||
       (flash_info.EraseSectorSize != 0x1000)  ||
       (flash_info.ProgPageSize != 0x100)      ||
	   (flash_info.EraseSectorsNumber != 4096) ||
       (flash_info.ProgPagesNumber != 65536))
    	return HAL_ERROR;

    status = Flash_Init_Tracks_Layout();
    if(status != HAL_OK) return status;

    return HAL_OK;
}
