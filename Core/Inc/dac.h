#pragma once

#include "stdio.h"
#include "string.h"
#include "stm32l4xx_hal.h"
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_audio.h"
#include "flash.h"

#define AUDIO_BUFFER_SIZE 256

HAL_StatusTypeDef dac_play_track(uint8_t track_id);


void AudioRecord_demo(void);
