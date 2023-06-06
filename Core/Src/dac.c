#include "dac.h"

static uint16_t audio_out_buffer[AUDIO_BUFFER_SIZE];

static void play_track_transfer_complete_callback() {
	uint16_t buffer_size = AUDIO_BUFFER_SIZE;

	buffer_size = Flash_Track_Play_Buffer_Read((uint8_t *)audio_out_buffer, buffer_size);

	if(buffer_size == 0) return;

    if (BSP_AUDIO_OUT_ChangeBuffer(audio_out_buffer, buffer_size) != 0) {
    	printf("Failed to change audio buffer to play\r\n");
    }
}

static void play_track_error_callback() {
	printf("Play track error callback\r\n");
}

HAL_StatusTypeDef dac_play_track(uint8_t track_id) {
	uint8_t volume = 25;
	uint32_t sample_rate = 44100;

	Flash_Track_Play_Start(track_id);

	if(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, volume, sample_rate) != AUDIO_OK) {
		printf("Failed to load audio output\r\n");
		return HAL_ERROR;
    }

    BSP_AUDIO_OUT_RegisterCallbacks(play_track_error_callback, NULL, play_track_transfer_complete_callback);

    if(BSP_AUDIO_OUT_SetVolume(volume) != 0) {
    	printf("Failed to set audio volume output\r\n");
    	return HAL_ERROR;
    }

    if(BSP_AUDIO_OUT_Play(audio_out_buffer, AUDIO_BUFFER_SIZE) != AUDIO_OK) {
    	printf("Failed to play audio\r\n");
    	return HAL_ERROR;
    }

    while (play_address < play_end_address);

    BSP_AUDIO_OUT_SetMute(AUDIO_MUTE_ON);
    HAL_Delay(20);

    if (BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW) != AUDIO_OK) {
    	printf("Failed to stop audio playing\r\n");
    	return HAL_ERROR;
    }

    return HAL_OK;
}
