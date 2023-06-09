/**
  ******************************************************************************
  * File Name          : LCD.h
  * Description        : This file provides code for the configuration
  *                      of the LCD instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __lcd_H
#define __lcd_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "stm32l476g_discovery.h"
#include "stm32l476g_discovery_glass_lcd.h"
/* USER CODE END Includes */

extern LCD_HandleTypeDef hlcd;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_LCD_Init(void);

/* USER CODE BEGIN Prototypes */

void display_lcd(char* str);
void lcd_init();
void lcd_deinit();

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ lcd_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
