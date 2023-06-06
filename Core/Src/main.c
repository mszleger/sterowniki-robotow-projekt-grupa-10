/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dfsdm.h"
#include "dma.h"
#include "i2c.h"
#include "lcd.h"
#include "quadspi.h"
#include "sai.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "flash.h"
#include "dac.h"
#include "joy.h"
#include "record.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAIN_MENU                   0
#define OPTION_RECORD 0
#define OPTION_PLAY   1
#define OPTION_DELETE 2
#define OPTION_AUTO   3

#define SUBMENU_RECORD_TRACK_SELECT 1

#define SUBMENU_PLAY_TRACK_SELECT   2

#define SUBMENU_DELETE_TRACK_SELECT 3

#define SUBMENU_AUTO_SWITCH         4

#define STATE_RECORGING             5
#define STATE_PLAYING               6
#define STATE_DELETING              7
#define STATE_SWITCHING             8

#define AUTO_DISABLED               0
#define AUTO_ENABLED                1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static uint8_t menu_structure[9][2] = {{0,3},{0,7},{0,7},{0,7},{0,1}};
static char* menu_text[9][8] = {{"RECORD", "PLAY", "DELETE", "AUTO"},
		                        {"TRACK1", "TRACK2", "TRACK3", "TRACK4", "TRACK5", "TRACK6", "TRACK7", "TRACK8"},
		                        {"TRACK1", "TRACK2", "TRACK3", "TRACK4", "TRACK5", "TRACK6", "TRACK7", "TRACK8"},
							    {"TRACK1", "TRACK2", "TRACK3", "TRACK4", "TRACK5", "TRACK6", "TRACK7", "TRACK8"},
							    {"OFF", "ON"}};
volatile uint8_t auto_status = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// Adding support of printf function - sending data over USART
int _write(int file, char *ptr, int len) {
  HAL_UART_Transmit(&huart2, ptr, len, 50);
  return len;
}
void update_menu(uint8_t submenu, uint8_t option) {
	display_lcd(menu_text[submenu][option]);
}
void update_joystick(struct joy* joystick, uint8_t* submenu, uint8_t* option) {
	static uint32_t joystick_event_id = 0;
	joy_up(joystick);
	joy_down(joystick);
	joy_left(joystick);
	joy_right(joystick);
	joy_center(joystick);
	if(joystick->tab[joystick_event_id] == -1) return; // NO NEW EVENT
	switch(joystick->tab[joystick_event_id]) {
		case 0: // UP - previous option
			if(menu_structure[*submenu][0] < *option) // Check if can go up
				--(*option);
			break;
		case 2: // DOWN - next option
			if(menu_structure[*submenu][1] > *option) // Check if can go up
				++(*option);
			break;
		case 1: // RIGHT - enter option
		case 4: // CENTER
			if(*submenu == MAIN_MENU) {
				*submenu = *option + 1;
				*option  = 0;
			} else {
				*submenu = *submenu + 4; // Go from selecting to state
			}
			break;
		case 3: // LEFT - go to previous submenu
			if(*submenu == SUBMENU_RECORD_TRACK_SELECT || *submenu == SUBMENU_PLAY_TRACK_SELECT ||
			   *submenu == SUBMENU_DELETE_TRACK_SELECT || *submenu == SUBMENU_AUTO_SWITCH) {
				*option  = *submenu - 1;
				*submenu = MAIN_MENU;
			}
			break;
		default:
			printf("Unknown key id: %d", joystick->tab[joystick_event_id]);
			break;
	}
	++joystick_event_id;
}
void record_track(uint8_t track_id) {
	int32_t buffer[256];
	if(Flash_Track_Status_Set(track_id, TRACK_SAVED) != HAL_OK) return;
	display_lcd("FLASHC");
	Flash_Track_Record_Start(track_id);
	display_lcd("REC");
	printf("Cleared flash space\r\n");
	do {
		record(buffer, 256);
	} while(Flash_Track_Record_Buffer_Save((uint8_t *)buffer, 256 * 4) == 256 * 4);
	display_lcd("DONE");
	HAL_Delay(1000);
}
void play_track(uint8_t track_id) {
	uint8_t track_state;
	if(Flash_Track_Status_Get(track_id, &track_state) != HAL_OK) return;
	if(track_state == TRACK_EMPTY) {
		display_lcd("EMPTY");
		HAL_Delay(1000);
		return;
	}
	if(dac_play_track(track_id) != HAL_OK) {
		printf("Failed to play track %d", track_id);
		return;
	}
	display_lcd("DONE");
	HAL_Delay(1000);
}
void delete_track(uint8_t track_id) {
	if(Flash_Track_Status_Set(track_id, TRACK_EMPTY) != HAL_OK) return;
	HAL_Delay(1000);
}
void switch_auto(uint8_t state) {
	auto_status = state;
	HAL_Delay(1000);
}
uint8_t is_there_conversation() {
	int32_t buffer;
	record(&buffer, 1);
	return abs(buffer) > 1000;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_QUADSPI_Init();
  MX_SAI1_Init();
  MX_USART2_UART_Init();
  MX_LCD_Init();
  MX_DFSDM1_Init();
  /* USER CODE BEGIN 2 */
  if(Flash_Init() != HAL_OK) {
	  printf("Flash init error\r\n");
	  while(1);
  }

  lcd_init();

  struct joy joystick;
  joy_init(&joystick);

  uint8_t submenu = 0;
  uint8_t option  = 0;
  uint8_t state = 0;
  uint8_t state_old = 255;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	// Joystick
	update_joystick(&joystick, &submenu, &option);
	// States handlers
    if(submenu == STATE_RECORGING) {
    	display_lcd("REC");
    	record_track(option);
    	submenu = MAIN_MENU;
    	option = 0;
    }
    if(submenu == STATE_PLAYING) {
    	display_lcd("PLAYIN");
    	play_track(option);
    	submenu = MAIN_MENU;
    	option = 0;
    }
    if(submenu == STATE_DELETING) {
    	display_lcd("DEL");
    	delete_track(option);
    	submenu = MAIN_MENU;
    	option = 0;
    }
    if(submenu == STATE_SWITCHING) {
    	display_lcd("SWITCH");
    	switch_auto(state);
    	submenu = MAIN_MENU;
    	option = 0;
    }
    // Conversation detector
    if(auto_status != AUTO_DISABLED) {
    	if(is_there_conversation()) {
        	display_lcd("REC");
        	record_track(0);
        	submenu = MAIN_MENU;
        	option = 0;
    	}
    }
	// LCD Update
	state = (10 * submenu) + option;
	if(state != state_old) {
		update_menu(submenu, option);
		state_old = state;
	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_SAI1|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_DFSDM1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI1;
  PeriphClkInit.Dfsdm1ClockSelection = RCC_DFSDM1CLKSOURCE_PCLK;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 48;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV17;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_SAI1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
