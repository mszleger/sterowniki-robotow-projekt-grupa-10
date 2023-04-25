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
#include <string.h>
#include <ctype.h>
/* USER CODE END Includes */

extern LCD_HandleTypeDef hlcd;
extern char* new_str;

extern uint32_t RAM0;
extern uint32_t RAM1;
extern uint32_t RAM2;
extern uint32_t RAM3;
extern uint32_t RAM4;
extern uint32_t RAM5;
extern uint32_t RAM6;
extern uint32_t RAM7;
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_LCD_Init(void);

/* USER CODE BEGIN Prototypes */

void display_lcd(char* str);
void LCD_A_1();
void LCD_B_1();
void LCD_C_1();
void LCD_D_1();
void LCD_E_1();
void LCD_F_1();
void LCD_G_1();
void LCD_H_1();
void LCD_I_1();
void LCD_J_1();
void LCD_K_1();
void LCD_L_1();
void LCD_M_1();
void LCD_N_1();
void LCD_O_1();
void LCD_U_1();
void LCD_P_1();
void LCD_R_1();
void LCD_S_1();
void LCD_T_1();
void LCD_W_1();
void LCD_Y_1();
void LCD_Z_1();
void LCD_0_1();
void LCD_1_1();
void LCD_2_1();
void LCD_3_1();
void LCD_4_1();
void LCD_5_1();
void LCD_6_1();
void LCD_7_1();
void LCD_8_1();
void LCD_9_1();



void LCD_A_2();
void LCD_B_2();
void LCD_C_2();
void LCD_D_2();
void LCD_E_2();
void LCD_F_2();
void LCD_G_2();
void LCD_H_2();
void LCD_I_2();
void LCD_J_2();
void LCD_K_2();
void LCD_L_2();
void LCD_M_2();
void LCD_N_2();
void LCD_O_2();
void LCD_U_2();
void LCD_P_2();
void LCD_R_2();
void LCD_S_2();
void LCD_T_2();
void LCD_W_2();
void LCD_Y_2();
void LCD_Z_2();
void LCD_0_2();
void LCD_1_2();
void LCD_2_2();
void LCD_3_2();
void LCD_4_2();
void LCD_5_2();
void LCD_6_2();
void LCD_7_2();
void LCD_8_2();
void LCD_9_2();

void LCD_A_5();
void LCD_B_5();
void LCD_C_5();
void LCD_D_5();
void LCD_E_5();
void LCD_F_5();
void LCD_G_5();
void LCD_H_5();
void LCD_I_5();
void LCD_J_5();
void LCD_K_5();
void LCD_L_5();
void LCD_M_5();
void LCD_N_5();
void LCD_O_5();
void LCD_U_5();
void LCD_P_5();
void LCD_R_5();
void LCD_S_5();
void LCD_T_5();
void LCD_W_5();
void LCD_Y_5();
void LCD_Z_5();
void LCD_0_5();
void LCD_1_5();
void LCD_2_5();
void LCD_3_5();
void LCD_4_5();
void LCD_5_5();
void LCD_6_5();
void LCD_7_5();
void LCD_8_5();
void LCD_9_5();

void LCD_A_6();
void LCD_B_6();
void LCD_C_6();
void LCD_D_6();
void LCD_E_6();
void LCD_F_6();
void LCD_G_6();
void LCD_H_6();
void LCD_I_6();
void LCD_J_6();
void LCD_K_6();
void LCD_L_6();
void LCD_M_6();
void LCD_N_6();
void LCD_O_6();
void LCD_U_6();
void LCD_P_6();
void LCD_R_6();
void LCD_S_6();
void LCD_T_6();
void LCD_W_6();
void LCD_Y_6();
void LCD_Z_6();
void LCD_0_6();
void LCD_1_6();
void LCD_2_6();
void LCD_3_6();
void LCD_4_6();
void LCD_5_6();
void LCD_6_6();
void LCD_7_6();
void LCD_8_6();
void LCD_9_6();
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
