#include "flash.h"

HAL_StatusTypeDef Flash_Init(void) {
	HAL_StatusTypeDef status;

	status = BSP_QSPI_Init();
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

HAL_StatusTypeDef Flash_Init_Tracks_Layout(void) {
	if(USER_DATA_BEGIN_ADDRESS + TRACK_AMOUNT + (TRACK_AMOUNT * TRACK_SPACE_LENGTH) > flash_info.FlashSize)
		return HAL_ERROR;

	for(uint32_t i = 0; i < TRACK_AMOUNT; ++i)
		track_status_address[i] = USER_DATA_BEGIN_ADDRESS + i;

	for(uint32_t i = 0; i < TRACK_AMOUNT; ++i)
		track_begin_address[i] = USER_DATA_BEGIN_ADDRESS + TRACK_AMOUNT + (i * TRACK_SPACE_LENGTH);

	return HAL_OK;
}

HAL_StatusTypeDef Flash_Test(void) {
	uint32_t buffer_tx_size = 256;
	uint32_t buffer_rx_size = 100;

	HAL_StatusTypeDef status;
	uint8_t buffer_tx[buffer_tx_size];
	uint8_t buffer_rx[buffer_rx_size];
	uint32_t bytes_tested = 0;

	// Filling tx buffer
	for(uint32_t i = 0; i < buffer_tx_size; ++i)
		buffer_tx[i] = i % 256;

	// Testing all records RW space
	for(uint8_t track = 0; track < TRACK_AMOUNT; ++track) {
		// Testing track status register
		uint8_t status_register_value = 0;
		status = Flash_Track_Status_Set(track, 150);
		if(status != HAL_OK) return status;
		status = Flash_Track_Status_Get(track, &status_register_value);
		if(status != HAL_OK) return status;
		if(status_register_value != 150) return HAL_ERROR;

		status = Flash_Track_Status_Set(track, 10);
		if(status != HAL_OK) return status;
		status = Flash_Track_Status_Get(track, &status_register_value);
		if(status != HAL_OK) return status;
		if(status_register_value != 10) return HAL_ERROR;

		// Start of recording
		status = Flash_Record_Start(track);
		if(status != HAL_OK) return status;
		// Recording
		while(Flash_Record_Save_Buffer(buffer_tx, buffer_tx_size) != buffer_tx_size);
		// Start of playing
		status = Flash_Play_Start(track);
		if(status != HAL_OK) return status;
		// Playing and values checking
		uint8_t expected_value = 0;
		uint32_t bytes_read = 0;
		do {
			bytes_read = Flash_Record_Save_Buffer(buffer_rx, buffer_rx_size);
			for(uint8_t i = 0; i < bytes_read; ++i) {
				if(buffer_rx[i] != expected_value) return HAL_ERROR;
				expected_value += 1;
				expected_value %= 256;
				bytes_tested += 1;
			}
		} while(bytes_read != buffer_rx_size);
	}

	printf("FLASH: Tested %ld bytes\r\n", bytes_tested);
	return HAL_OK;
}

HAL_StatusTypeDef Flash_Track_Status_Set(uint8_t track_number, uint8_t new_track_status) {
	HAL_StatusTypeDef status;

	if(track_number >= TRACK_AMOUNT) return HAL_ERROR;

	status = BSP_QSPI_Write(&new_track_status, track_status_address[track_number], 1);
	if(status != HAL_OK) return status;

	return HAL_OK;
}

HAL_StatusTypeDef Flash_Track_Status_Get(uint8_t track_number, uint8_t* track_status) {
	HAL_StatusTypeDef status;

	if(track_number >= TRACK_AMOUNT) return HAL_ERROR;

	status = BSP_QSPI_Read(track_status, track_status_address[track_number], 1);
	if(status != HAL_OK) return status;

	return HAL_OK;
}

HAL_StatusTypeDef Flash_Record_Start(uint8_t track_number) {
	if(track_number >= TRACK_AMOUNT) return HAL_ERROR;

	record_address = track_begin_address[track_number];
	record_end_address = track_begin_address[track_number] + TRACK_SPACE_LENGTH;

	return HAL_OK;
}

uint32_t Flash_Record_Save_Buffer(uint8_t* buffer, uint32_t buffer_length) {
	if(buffer_length > record_end_address - record_address)
		buffer_length = record_end_address - record_address;

	if(BSP_QSPI_Write(buffer, record_address, buffer_length) != HAL_OK)
		return 0;

	record_address += buffer_length;

	return buffer_length;
}

HAL_StatusTypeDef Flash_Play_Start(uint8_t track_number) {
	if(track_number >= TRACK_AMOUNT) return HAL_ERROR;

	play_address = track_begin_address[track_number];
	play_end_address = track_begin_address[track_number] + TRACK_SPACE_LENGTH;

	return HAL_OK;
}

uint32_t Flash_Play_Read_Buffer(uint8_t* buffer, uint32_t buffer_length) {
	if(buffer_length > play_end_address - play_address)
		buffer_length = play_end_address - play_address;

	if(BSP_QSPI_Read(buffer, play_address, buffer_length) != HAL_OK)
		return 0;

	play_address += buffer_length;

	return buffer_length;
}















































