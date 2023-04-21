/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SAI1_MCK_Pin GPIO_PIN_2
#define SAI1_MCK_GPIO_Port GPIOE
#define DAC_AUDIO_RST_Pin GPIO_PIN_3
#define DAC_AUDIO_RST_GPIO_Port GPIOE
#define SAI1_FS_Pin GPIO_PIN_4
#define SAI1_FS_GPIO_Port GPIOE
#define SAI1_SCK_Pin GPIO_PIN_5
#define SAI1_SCK_GPIO_Port GPIOE
#define SAI1_SD_Pin GPIO_PIN_6
#define SAI1_SD_GPIO_Port GPIOE
#define JOY_CENTER_Pin GPIO_PIN_0
#define JOY_CENTER_GPIO_Port GPIOA
#define JOY_LEFT_Pin GPIO_PIN_1
#define JOY_LEFT_GPIO_Port GPIOA
#define JOY_RIGHT_Pin GPIO_PIN_2
#define JOY_RIGHT_GPIO_Port GPIOA
#define JOY_UP_Pin GPIO_PIN_3
#define JOY_UP_GPIO_Port GPIOA
#define JOY_DOWN_Pin GPIO_PIN_5
#define JOY_DOWN_GPIO_Port GPIOA
#define LCD_SEG_23_Pin GPIO_PIN_6
#define LCD_SEG_23_GPIO_Port GPIOA
#define LCD_SEG_0_Pin GPIO_PIN_7
#define LCD_SEG_0_GPIO_Port GPIOA
#define LCD_SEG_22_Pin GPIO_PIN_4
#define LCD_SEG_22_GPIO_Port GPIOC
#define LCD_SEG_1_Pin GPIO_PIN_5
#define LCD_SEG_1_GPIO_Port GPIOC
#define LCD_SEG_21_Pin GPIO_PIN_0
#define LCD_SEG_21_GPIO_Port GPIOB
#define LCD_SEG_2_Pin GPIO_PIN_1
#define LCD_SEG_2_GPIO_Port GPIOB
#define MIC_AUDIO_DIN_Pin GPIO_PIN_7
#define MIC_AUDIO_DIN_GPIO_Port GPIOE
#define MIC_AUDIO_CLK_Pin GPIO_PIN_9
#define MIC_AUDIO_CLK_GPIO_Port GPIOE
#define QSPI_CLK_Pin GPIO_PIN_10
#define QSPI_CLK_GPIO_Port GPIOE
#define QSPI_CS_Pin GPIO_PIN_11
#define QSPI_CS_GPIO_Port GPIOE
#define QSPI_D0_Pin GPIO_PIN_12
#define QSPI_D0_GPIO_Port GPIOE
#define QSPI_D1_Pin GPIO_PIN_13
#define QSPI_D1_GPIO_Port GPIOE
#define QSPI_D2_Pin GPIO_PIN_14
#define QSPI_D2_GPIO_Port GPIOE
#define QSPI_D3_Pin GPIO_PIN_15
#define QSPI_D3_GPIO_Port GPIOE
#define LCD_SEG_20_Pin GPIO_PIN_12
#define LCD_SEG_20_GPIO_Port GPIOB
#define LCD_SEG_3_Pin GPIO_PIN_13
#define LCD_SEG_3_GPIO_Port GPIOB
#define LCD_SEG_19_Pin GPIO_PIN_14
#define LCD_SEG_19_GPIO_Port GPIOB
#define LCD_SEG_4_Pin GPIO_PIN_15
#define LCD_SEG_4_GPIO_Port GPIOB
#define LCD_SEG_18_Pin GPIO_PIN_8
#define LCD_SEG_18_GPIO_Port GPIOD
#define LCD_SEG_5_Pin GPIO_PIN_9
#define LCD_SEG_5_GPIO_Port GPIOD
#define LCD_SEG_17_Pin GPIO_PIN_10
#define LCD_SEG_17_GPIO_Port GPIOD
#define LCD_SEG_6_Pin GPIO_PIN_11
#define LCD_SEG_6_GPIO_Port GPIOD
#define LCD_SEG_16_Pin GPIO_PIN_12
#define LCD_SEG_16_GPIO_Port GPIOD
#define LCD_SEG_7_Pin GPIO_PIN_13
#define LCD_SEG_7_GPIO_Port GPIOD
#define LCD_SEG_15_Pin GPIO_PIN_14
#define LCD_SEG_15_GPIO_Port GPIOD
#define LCD_SEG_8_Pin GPIO_PIN_15
#define LCD_SEG_8_GPIO_Port GPIOD
#define LCD_SEG_14_Pin GPIO_PIN_6
#define LCD_SEG_14_GPIO_Port GPIOC
#define LCD_SEG_9_Pin GPIO_PIN_7
#define LCD_SEG_9_GPIO_Port GPIOC
#define LCD_SEG_13_Pin GPIO_PIN_8
#define LCD_SEG_13_GPIO_Port GPIOC
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define LCD_SEG_10_Pin GPIO_PIN_15
#define LCD_SEG_10_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_5
#define USART_TX_GPIO_Port GPIOD
#define USART_RX_Pin GPIO_PIN_6
#define USART_RX_GPIO_Port GPIOD
#define M3V3_REG_ON_Pin GPIO_PIN_3
#define M3V3_REG_ON_GPIO_Port GPIOB
#define LCD_SEG_11_Pin GPIO_PIN_4
#define LCD_SEG_11_GPIO_Port GPIOB
#define LCD_SEG_12_Pin GPIO_PIN_5
#define LCD_SEG_12_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_6
#define I2C1_SCL_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_7
#define I2C1_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
