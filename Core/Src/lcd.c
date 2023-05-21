/**
  ******************************************************************************
  * File Name          : LCD.c
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

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

LCD_HandleTypeDef hlcd;
 uint32_t RAM0;
 uint32_t RAM1;
 uint32_t RAM2;
 uint32_t RAM3;
 uint32_t RAM4;
 uint32_t RAM5;
 uint32_t RAM6;
 uint32_t RAM7;
char* new_str;
/* LCD init function */
void MX_LCD_Init(void)
{

  hlcd.Instance = LCD;
  hlcd.Init.Prescaler = LCD_PRESCALER_1;
  hlcd.Init.Divider = LCD_DIVIDER_16;
  hlcd.Init.Duty = LCD_DUTY_1_4;
  hlcd.Init.Bias = LCD_BIAS_1_4;
  hlcd.Init.VoltageSource = LCD_VOLTAGESOURCE_INTERNAL;
  hlcd.Init.Contrast = LCD_CONTRASTLEVEL_0;
  hlcd.Init.DeadTime = LCD_DEADTIME_0;
  hlcd.Init.PulseOnDuration = LCD_PULSEONDURATION_0;
  hlcd.Init.MuxSegment = LCD_MUXSEGMENT_ENABLE;
  hlcd.Init.BlinkMode = LCD_BLINKMODE_OFF;
  hlcd.Init.BlinkFrequency = LCD_BLINKFREQUENCY_DIV8;
  hlcd.Init.HighDrive = LCD_HIGHDRIVE_DISABLE;
  if (HAL_LCD_Init(&hlcd) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_LCD_MspInit(LCD_HandleTypeDef* lcdHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(lcdHandle->Instance==LCD)
  {
  /* USER CODE BEGIN LCD_MspInit 0 */

  /* USER CODE END LCD_MspInit 0 */
    /* LCD clock enable */
    __HAL_RCC_LCD_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**LCD GPIO Configuration
    PC3     ------> LCD_VLCD
    PA6     ------> LCD_SEG3
    PA7     ------> LCD_SEG4
    PC4     ------> LCD_SEG22
    PC5     ------> LCD_SEG23
    PB0     ------> LCD_SEG5
    PB1     ------> LCD_SEG6
    PB12     ------> LCD_SEG12
    PB13     ------> LCD_SEG13
    PB14     ------> LCD_SEG14
    PB15     ------> LCD_SEG15
    PD8     ------> LCD_SEG28
    PD9     ------> LCD_SEG29
    PD10     ------> LCD_SEG30
    PD11     ------> LCD_SEG31
    PD12     ------> LCD_SEG32
    PD13     ------> LCD_SEG33
    PD14     ------> LCD_SEG34
    PD15     ------> LCD_SEG35
    PC6     ------> LCD_SEG24
    PC7     ------> LCD_SEG25
    PC8     ------> LCD_SEG26
    PA8     ------> LCD_COM0
    PA9     ------> LCD_COM1
    PA10     ------> LCD_COM2
    PA15 (JTDI)     ------> LCD_SEG17
    PB4 (NJTRST)     ------> LCD_SEG8
    PB5     ------> LCD_SEG9
    PB9     ------> LCD_COM3
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|LCD_SEG_22_Pin|LCD_SEG_1_Pin|LCD_SEG_14_Pin
                          |LCD_SEG_9_Pin|LCD_SEG_13_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_SEG_23_Pin|LCD_SEG_0_Pin|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|LCD_SEG_10_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_SEG_21_Pin|LCD_SEG_2_Pin|LCD_SEG_20_Pin|LCD_SEG_3_Pin
                          |LCD_SEG_19_Pin|LCD_SEG_4_Pin|LCD_SEG_11_Pin|LCD_SEG_12_Pin
                          |GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LCD_SEG_18_Pin|LCD_SEG_5_Pin|LCD_SEG_17_Pin|LCD_SEG_6_Pin
                          |LCD_SEG_16_Pin|LCD_SEG_7_Pin|LCD_SEG_15_Pin|LCD_SEG_8_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF11_LCD;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN LCD_MspInit 1 */

  /* USER CODE END LCD_MspInit 1 */
  }
}

void HAL_LCD_MspDeInit(LCD_HandleTypeDef* lcdHandle)
{

  if(lcdHandle->Instance==LCD)
  {
  /* USER CODE BEGIN LCD_MspDeInit 0 */

  /* USER CODE END LCD_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LCD_CLK_DISABLE();

    /**LCD GPIO Configuration
    PC3     ------> LCD_VLCD
    PA6     ------> LCD_SEG3
    PA7     ------> LCD_SEG4
    PC4     ------> LCD_SEG22
    PC5     ------> LCD_SEG23
    PB0     ------> LCD_SEG5
    PB1     ------> LCD_SEG6
    PB12     ------> LCD_SEG12
    PB13     ------> LCD_SEG13
    PB14     ------> LCD_SEG14
    PB15     ------> LCD_SEG15
    PD8     ------> LCD_SEG28
    PD9     ------> LCD_SEG29
    PD10     ------> LCD_SEG30
    PD11     ------> LCD_SEG31
    PD12     ------> LCD_SEG32
    PD13     ------> LCD_SEG33
    PD14     ------> LCD_SEG34
    PD15     ------> LCD_SEG35
    PC6     ------> LCD_SEG24
    PC7     ------> LCD_SEG25
    PC8     ------> LCD_SEG26
    PA8     ------> LCD_COM0
    PA9     ------> LCD_COM1
    PA10     ------> LCD_COM2
    PA15 (JTDI)     ------> LCD_SEG17
    PB4 (NJTRST)     ------> LCD_SEG8
    PB5     ------> LCD_SEG9
    PB9     ------> LCD_COM3
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_3|LCD_SEG_22_Pin|LCD_SEG_1_Pin|LCD_SEG_14_Pin
                          |LCD_SEG_9_Pin|LCD_SEG_13_Pin);

    HAL_GPIO_DeInit(GPIOA, LCD_SEG_23_Pin|LCD_SEG_0_Pin|GPIO_PIN_8|GPIO_PIN_9
                          |GPIO_PIN_10|LCD_SEG_10_Pin);

    HAL_GPIO_DeInit(GPIOB, LCD_SEG_21_Pin|LCD_SEG_2_Pin|LCD_SEG_20_Pin|LCD_SEG_3_Pin
                          |LCD_SEG_19_Pin|LCD_SEG_4_Pin|LCD_SEG_11_Pin|LCD_SEG_12_Pin
                          |GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOD, LCD_SEG_18_Pin|LCD_SEG_5_Pin|LCD_SEG_17_Pin|LCD_SEG_6_Pin
                          |LCD_SEG_16_Pin|LCD_SEG_7_Pin|LCD_SEG_15_Pin|LCD_SEG_8_Pin);

  /* USER CODE BEGIN LCD_MspDeInit 1 */

  /* USER CODE END LCD_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void LCD_A_1(){
	//HAL_LCD_Write(&hlcd, 0, 0, 1U << 3 | 1U << 4 | 1U << 22 | 1U << 23);
  //  HAL_LCD_Write(&hlcd, 2, 0, 1U << 3 | 1U << 22 | 1U << 23);
    RAM0 += 1U << 3 | 1U << 4 | 1U << 22 | 1U << 23;
    RAM2 += 1U << 3 | 1U << 22 | 1U << 23;
  //  HAL_LCD_UpdateDisplayRequest(&hlcd);
}
void LCD_B_1(){
	//HAL_LCD_Write(&hlcd, 0, 0, 1U << 3 | 1U << 23| 1U << 4 );
	//HAL_LCD_Write(&hlcd, 2, 0,  1U << 3 | 1U << 23 | 1U << 4 );
	RAM0 += 1U << 3 | 1U << 23| 1U << 4;
	RAM2 +=1U << 3 | 1U << 23 | 1U << 4;
	//HAL_LCD_UpdateDisplayRequest(&hlcd);
}
void LCD_C_1(){
	//HAL_LCD_Write(&hlcd, 0, 0, 1U << 4 );
	//HAL_LCD_Write(&hlcd, 2, 0,  1U << 3 | 1U << 4 | 1U << 22);
	//HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 4;
	RAM2 += 1U << 3 | 1U << 4 | 1U << 22;
}

void LCD_D_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 3 | 1U << 23| 1U << 4 | 1U << 22 );
//	HAL_LCD_Write(&hlcd, 2, 0,  1U << 4 | 1U << 23);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 3 | 1U << 23| 1U << 4 | 1U << 22;
	RAM2 += 1U << 4 | 1U << 23;
}

void LCD_E_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 4 | 1U << 3 |1U << 23);
//	HAL_LCD_Write(&hlcd, 2, 0,  1U << 3 | 1U << 4 | 1U << 22 );
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 4 | 1U << 3 |1U << 23;
	RAM2 += 1U << 3 | 1U << 4 | 1U << 22;
}

void LCD_F_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 4 | 1U << 3 |1U << 23);
	//HAL_LCD_Write(&hlcd, 2, 0,  1U << 3 | 1U << 22 );
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 4 | 1U << 3 |1U << 23;
	RAM2 += 1U << 3 | 1U << 22 ;
}

void LCD_G_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 4 | 1U << 23);
//	HAL_LCD_Write(&hlcd, 2, 0,  1U << 3 | 1U << 4 | 1U << 22 | 1U << 23);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 4 | 1U << 23;
	RAM2 += 1U << 3 | 1U << 4 | 1U << 22 | 1U << 23;
}

void LCD_H_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 3 | 1U << 4 | 1U << 23);
//    HAL_LCD_Write(&hlcd, 2, 0, 1U << 3 | 1U << 23);
 //   HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 3 | 1U << 4 | 1U << 23;
	RAM2 += 1U << 3 | 1U << 23;
}

void LCD_I_1(){
   // HAL_LCD_Write(&hlcd, 2, 0, 1U << 23 | 1U << 22);
  //  HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM2 += 1U << 23 | 1U << 22;
}

void LCD_J_1(){
 //   HAL_LCD_Write(&hlcd, 2, 0, 1U << 23 | 1U << 22 | 1U << 4);
 //   HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM2 += 1U << 23 | 1U << 22 | 1U << 4;
}

void LCD_K_1(){
	//HAL_LCD_Write(&hlcd, 0, 0, 1U << 3 | 1U << 4 );
   // HAL_LCD_Write(&hlcd, 2, 0, 1U << 3 );
   // HAL_LCD_Write(&hlcd, 4, 0, 1U << 22 );
   // HAL_LCD_Write(&hlcd, 6, 0, 1U << 4 );
   // HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 3 | 1U << 4;
	RAM2 += 1U << 3 ;
	RAM4 += 1U << 22 ;
	RAM6 += 1U << 4 ;
}

void LCD_L_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 4 );
//	HAL_LCD_Write(&hlcd, 2, 0,  1U << 3 | 1U << 4);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0+= 1U << 4 ;
	RAM2+=1U << 3 | 1U << 4;
}

void LCD_M_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 3 | 1U << 23| 1U << 4);
//	HAL_LCD_Write(&hlcd, 2, 0,  1U << 23);
//	HAL_LCD_Write(&hlcd, 4, 0,1U << 4);

	//HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 3 | 1U << 23| 1U << 4;
	RAM2 += 1U << 23;
	RAM4 += 1U << 4;
}

void LCD_N_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 3 | 1U << 23| 1U << 4);
//	HAL_LCD_Write(&hlcd, 2, 0,  1U << 23);

//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 3 | 1U << 23| 1U << 4;
	RAM2 += 1U << 23;
}

void LCD_O_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 3 | 1U << 23| 1U << 4);
//	HAL_LCD_Write(&hlcd, 2, 0,  1U << 23 | 1U << 4);

//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 3 | 1U << 23| 1U << 4;
	RAM2 += 1U << 23 | 1U << 4;
}

void LCD_U_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 4 | 1U << 22);
//	HAL_LCD_Write(&hlcd, 2, 0,  1U << 3 | 1U << 4| 1U << 23);

	//HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 4 | 1U << 22;
	RAM2 += 1U << 3 | 1U << 4| 1U << 23;
}

void LCD_P_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 4 | 1U << 3 |1U << 23|1U << 22);
///	HAL_LCD_Write(&hlcd, 2, 0,  1U << 3 | 1U << 22 );
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 4 | 1U << 3 |1U << 23|1U << 22;
	RAM2 += 1U << 3 | 1U << 22;
}

void LCD_R_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 4 | 1U << 3 |1U << 23|1U << 22);
//	HAL_LCD_Write(&hlcd, 2, 0,  1U << 3 | 1U << 22 );
//	HAL_LCD_Write(&hlcd, 4, 0,1U << 4);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 4 | 1U << 3 |1U << 23|1U << 22;
	RAM2 += 1U << 3 | 1U << 22;
	RAM4 += 1U << 4;
}

void LCD_S_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 3 |  1U << 23);
 //   HAL_LCD_Write(&hlcd, 2, 0, 1U << 3 | 1U << 22 | 1U << 23| 1U << 4);
 //   HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 3 |  1U << 23;
	RAM2 += 1U << 3 | 1U << 22 | 1U << 23| 1U << 4;
}

void LCD_T_1(){
//	HAL_LCD_Write(&hlcd, 2, 0,1U << 22);
//	HAL_LCD_Write(&hlcd, 4, 0,1U << 4);
//	HAL_LCD_Write(&hlcd, 6, 0,1U << 22);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM2 += 1U << 22;
	RAM4 += 1U << 4;
	RAM6 += 1U << 22;
}

void LCD_W_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 4 );
//	HAL_LCD_Write(&hlcd, 2, 0,  1U << 4| 1U << 23);
//	HAL_LCD_Write(&hlcd, 4, 0,1U << 4);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 4 ;
	RAM2 += 1U << 4| 1U << 23;
	RAM4 += 1U << 4;
}

void LCD_Y_1(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 3 | 1U << 23 | 1U << 22);
//	HAL_LCD_Write(&hlcd, 2, 0, 1U << 3 );
//	HAL_LCD_Write(&hlcd, 4, 0,1U << 4);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 3 | 1U << 23 | 1U << 22;
	RAM2 += 1U << 3;
	RAM4 += 1U << 4;
}

void LCD_Z_1(){
//	HAL_LCD_Write(&hlcd, 2, 0, 1U << 22 | 1U << 4);
//	HAL_LCD_Write(&hlcd, 4, 0, 1U << 22 | 1U << 3);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM2 += 1U << 22 | 1U << 4;
	RAM4 += 1U << 22 | 1U << 3;
}

void LCD_0_1(){
	 RAM0 += 1U << 22|1U << 4;
	 RAM2 += 1U << 23 |1U << 22 |1U << 3|1U << 4;

}
void LCD_1_1(){

	 RAM0 += 1U << 22;
	 RAM2 += 1U << 23;
}
void LCD_2_1(){
	RAM0 += 1U << 3 |  1U << 23|  1U << 22|  1U << 4;
	RAM2 += 1U << 22 | 1U << 4;
}
void LCD_3_1(){
	 RAM0 += 1U << 22 |  1U << 23 |  1U << 3;
	 RAM2 += 1U << 23 |  1U << 22|  1U << 4;
}
void LCD_4_1(){
	 RAM0 += 1U << 22 |  1U << 23 |  1U << 3;
	 RAM2 += 1U << 23 |  1U << 3;
}
void LCD_5_1(){
	RAM0 += 1U << 3 |  1U << 23;
	RAM2 += 1U << 3 | 1U << 22 | 1U << 23| 1U << 4;
}
void LCD_6_1(){
	RAM0 += 1U << 3 | 1U << 23| 1U << 4;
	RAM2 +=1U << 3 | 1U << 23 | 1U << 4 | 1U << 22;
}
void LCD_7_1(){
	 RAM0 += 1U << 22;
	 RAM2 += 1U << 23 | 1U << 22;
}
void LCD_8_1(){
	 RAM0 += 1U << 22|1U << 4|1U << 3|1U << 23;
	 RAM2 += 1U << 23 |1U << 22 |1U << 3|1U << 4;
}
void LCD_9_1(){
	 RAM0 += 1U << 22|1U << 3|1U << 23;
	 RAM2 += 1U << 23 |1U << 22 |1U << 3|1U << 4;
}








void display_lcd(char* str){
	if (strcmp(str, new_str) != 0)
	{
	HAL_LCD_Clear(&hlcd);
    int len = strlen(str);
    char h;
    char c;
    RAM0 = 0;
    RAM1 = 0;
    RAM2 = 0;
    RAM3 = 0;
    RAM4 = 0;
    RAM5 = 0;
    RAM6 = 0;
    RAM7 = 0;
    if (len >= 1){
        switch (str[0])
        {
        case 'a':
        	LCD_A_1();
            break;
        case 'b':
        	LCD_B_1();
            break;
        case 'c':
        	LCD_C_1();
            break;
        case 'd':
        	LCD_D_1();
            break;
        case 'e':
        	LCD_E_1();
            break;
        case 'f':
        	LCD_F_1();
            break;
        case 'g':
        	LCD_G_1();
            break;
        case 'h':
        	LCD_H_1();
            break;
        case 'i':
        	LCD_I_1();
            break;
        case 'j':
        	LCD_J_1();
            break;
        case 'k':
        	LCD_K_1();
            break;
        case 'l':
        	LCD_L_1();
            break;
        case 'm':
        	LCD_M_1();
            break;
        case 'n':
        	LCD_N_1();
            break;
        case 'o':
        	LCD_O_1();
            break;
        case 'u':
        	LCD_U_1();
            break;
        case 'p':
        	LCD_P_1();
            break;
        case 'r':
        	LCD_R_1();
            break;
        case 's':
        	LCD_S_1();
            break;
        case 't':
        	LCD_T_1();
            break;
        case 'w':
        	LCD_W_1();
            break;
        case 'y':
        	LCD_Y_1();
            break;
        case 'z':
        	LCD_Z_1();
            break;
        case '0':
        	LCD_0_1();
            break;
        case '1':
        	LCD_1_1();
            break;
        case '2':
        	LCD_2_1();
            break;
        case '3':
        	LCD_3_1();
            break;
        case '4':
        	LCD_4_1();
            break;
        case '5':
        	LCD_5_1();
            break;
        case '6':
        	LCD_6_1();
            break;
        case '7':
        	LCD_7_1();
            break;
        case '8':
        	LCD_8_1();
            break;
        case '9':
        	LCD_9_1();
            break;

        default:
            break;
        }
    }
    if (len >= 2){
        switch (str[1])
        {
                case 'a':
                	LCD_A_2();
                    break;
                case 'b':
                	LCD_B_2();
                    break;
                case 'c':
                	LCD_C_2();
                    break;
                case 'd':
                	LCD_D_2();
                    break;
                case 'e':
                	LCD_E_2();
                    break;
                case 'f':
                	LCD_F_2();
                    break;
                case 'g':
                	LCD_G_2();
                    break;
                case 'h':
                	LCD_H_2();
                    break;
                case 'i':
                	LCD_I_2();
                    break;
                case 'j':
                	LCD_J_2();
                    break;
                case 'k':
                	LCD_K_2();
                    break;
                case 'l':
                	LCD_L_2();
                    break;
                case 'm':
                	LCD_M_2();
                    break;
                case 'n':
                	LCD_N_2();
                    break;
                case 'o':
                	LCD_O_2();
                    break;
                case 'u':
                	LCD_U_2();
                    break;
                case 'p':
                	LCD_P_2();
                    break;
                case 'r':
                	LCD_R_2();
                    break;
                case 's':
                	LCD_S_2();
                    break;
                case 't':
                	LCD_T_2();
                    break;
                case 'w':
                	LCD_W_2();
                    break;
                case 'y':
                	LCD_Y_2();
                    break;
                case 'z':
                	LCD_Z_2();
                    break;
                case '0':
                	LCD_0_2();
                    break;
                case '1':
                	LCD_1_2();
                    break;
                case '2':
                	LCD_2_2();
                    break;
                case '3':
                	LCD_3_2();
                    break;
                case '4':
                	LCD_4_2();
                    break;
                case '5':
                	LCD_5_2();
                    break;
                case '6':
                	LCD_6_2();
                    break;
                case '7':
                	LCD_7_2();
                    break;
                case '8':
                	LCD_8_2();
                    break;
                case '9':
                	LCD_9_2();
                    break;

                default:
                    break;
                }
    }
   /* if (len >= 3){
    	if(isupper(str[2])){
    		str[2] = tolower(str[2]);
    	}
        switch (str[2])
        {
        case 's':

            break;

        default:
            break;
        }
    }*/
  /*  if (len >= 4){
    	if(isupper(str[3])){
    		str[3] = tolower(str[3]);
    	}
        switch (str[3])
        {
        case 'c':

            break;

        default:
            break;
        }
    }*/
    if (len >= 5){
        switch (str[4])
        {
                case 'a':
                	LCD_A_5();
                    break;
                case 'b':
                	LCD_B_5();
                    break;
                case 'c':
                	LCD_C_5();
                    break;
                case 'd':
                	LCD_D_5();
                    break;
                case 'e':
                	LCD_E_5();
                    break;
                case 'f':
                	LCD_F_5();
                    break;
                case 'g':
                	LCD_G_5();
                    break;
                case 'h':
                	LCD_H_5();
                    break;
                case 'i':
                	LCD_I_5();
                    break;
                case 'j':
                	LCD_J_5();
                    break;
                case 'k':
                	LCD_K_5();
                    break;
                case 'l':
                	LCD_L_5();
                    break;
                case 'm':
                	LCD_M_5();
                    break;
                case 'n':
                	LCD_N_5();
                    break;
                case 'o':
                	LCD_O_5();
                    break;
                case 'u':
                	LCD_U_5();
                    break;
                case 'p':
                	LCD_P_5();
                    break;
                case 'r':
                	LCD_R_5();
                    break;
                case 's':
                	LCD_S_5();
                    break;
                case 't':
                	LCD_T_5();
                    break;
                case 'w':
                	LCD_W_5();
                    break;
                case 'y':
                	LCD_Y_5();
                    break;
                case 'z':
                	LCD_Z_5();
                    break;
                case '0':
                	LCD_0_5();
                    break;
                case '1':
                	LCD_1_5();
                    break;
                case '2':
                	LCD_2_5();
                    break;
                case '3':
                	LCD_3_5();
                    break;
                case '4':
                	LCD_4_5();
                    break;
                case '5':
                	LCD_5_5();
                    break;
                case '6':
                	LCD_6_5();
                    break;
                case '7':
                	LCD_7_5();
                    break;
                case '8':
                	LCD_8_5();
                    break;
                case '9':
                	LCD_9_5();
                    break;

                default:
                    break;
                }
    }
    if (len >= 6){
        switch (str[5])
        {
                case 'a':
                	LCD_A_6();
                    break;
                case 'b':
                	LCD_B_6();
                    break;
                case 'c':
                	LCD_C_6();
                    break;
                case 'd':
                	LCD_D_6();
                    break;
                case 'e':
                	LCD_E_6();
                    break;
                case 'f':
                	LCD_F_6();
                    break;
                case 'g':
                	LCD_G_6();
                    break;
                case 'h':
                	LCD_H_6();
                    break;
                case 'i':
                	LCD_I_6();
                    break;
                case 'j':
                	LCD_J_6();
                    break;
                case 'k':
                	LCD_K_6();
                    break;
                case 'l':
                	LCD_L_6();
                    break;
                case 'm':
                	LCD_M_6();
                    break;
                case 'n':
                	LCD_N_6();
                    break;
                case 'o':
                	LCD_O_6();
                    break;
                case 'u':
                	LCD_U_6();
                    break;
                case 'p':
                	LCD_P_6();
                    break;
                case 'r':
                	LCD_R_6();
                    break;
                case 's':
                	LCD_S_6();
                    break;
                case 't':
                	LCD_T_6();
                    break;
                case 'w':
                	LCD_W_6();
                    break;
                case 'y':
                	LCD_Y_6();
                    break;
                case 'z':
                	LCD_Z_6();
                    break;
                case '0':
                	LCD_0_6();
                    break;
                case '1':
                	LCD_1_6();
                    break;
                case '2':
                	LCD_2_6();
                    break;
                case '3':
                	LCD_3_6();
                    break;
                case '4':
                	LCD_4_6();
                    break;
                case '5':
                	LCD_5_6();
                    break;
                case '6':
                	LCD_6_6();
                    break;
                case '7':
                	LCD_7_6();
                    break;
                case '8':
                	LCD_8_6();
                    break;
                case '9':
                	LCD_9_6();
                    break;
                default:
                    break;
                }
    }
    new_str = str;
}
	  HAL_LCD_Write(&hlcd, 0, 0, RAM0);
	  HAL_LCD_Write(&hlcd, 1, 0, RAM1);
	  HAL_LCD_Write(&hlcd, 2, 0, RAM2);
	  HAL_LCD_Write(&hlcd, 3, 0, RAM3);
	  HAL_LCD_Write(&hlcd, 4, 0, RAM4);
	  HAL_LCD_Write(&hlcd, 5, 0, RAM5);
	  HAL_LCD_Write(&hlcd, 6, 0, RAM6);
	  HAL_LCD_Write(&hlcd, 7, 0, RAM7);
	  HAL_LCD_UpdateDisplayRequest(&hlcd);
}


void LCD_A_2(){
	RAM0 += 1U << 6 | 1U << 13 | 1U << 5 | 1U << 12;
	RAM2 += 1U << 13 | 1U << 12 | 1U << 5;
}
void LCD_B_2(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 13 | 1U << 5);
  //  HAL_LCD_Write(&hlcd, 2, 0, 1U << 13| 1U << 5 | 1U << 6);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6 | 1U << 13 | 1U << 5;
	RAM2 += 1U << 13| 1U << 5 | 1U << 6;
}

void LCD_C_2(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 );
//   HAL_LCD_Write(&hlcd, 2, 0, 1U << 5 | 1U << 6 | 1U << 12);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6;
	RAM2 += 1U << 5 | 1U << 6 | 1U << 12;

}

void LCD_D_2(){
	//HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 13 | 1U << 5 | 1U << 12);
   // HAL_LCD_Write(&hlcd, 2, 0, 1U << 13| 1U << 6);
	RAM0 += 1U << 6 | 1U << 13 | 1U << 5 | 1U << 12;
	RAM2 += 1U << 13| 1U << 6;
	//HAL_LCD_UpdateDisplayRequest(&hlcd);
}

void LCD_E_2(){
	//HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 5 | 1U << 13);
	//HAL_LCD_Write(&hlcd, 2, 0, 1U << 5 | 1U << 6 | 1U << 12);
  // HAL_LCD_UpdateDisplayRequest(&hlcd);
   RAM0 += 1U << 6 | 1U << 5 | 1U << 13;
   RAM2 += 1U << 5 | 1U << 6 | 1U << 12;
}

void LCD_F_2(){
	//HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 5 | 1U << 13);
	  //  HAL_LCD_Write(&hlcd, 2, 0, 1U << 5 |  1U << 12);
		//HAL_LCD_UpdateDisplayRequest(&hlcd);

		RAM0 += 1U << 6 | 1U << 5 | 1U << 13;
		 RAM2 += 1U << 5 |  1U << 12;
}

void LCD_G_2(){
	//HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 13 );
	//    HAL_LCD_Write(&hlcd, 2, 0, 1U << 5 | 1U << 6 | 1U << 12 | 1U << 13);
	//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6 | 1U << 13;
	RAM2 += 1U << 5 | 1U << 6 | 1U << 12 | 1U << 13;

}

void LCD_H_2(){
	//HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 13 | 1U << 5);
	//    HAL_LCD_Write(&hlcd, 2, 0, 1U << 13 | 1U << 5);
	//    HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6 | 1U << 13 | 1U << 5;
	RAM2 += 1U << 13 | 1U << 5;
}

void LCD_I_2(){
	//    HAL_LCD_Write(&hlcd, 2, 0, 1U << 13 | 1U << 12);
	//    HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM2 += 1U << 13 | 1U << 12;
}

void LCD_J_2(){
	//    HAL_LCD_Write(&hlcd, 2, 0, 1U << 13 | 1U << 12 | 1U << 6);
	//    HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM2 += 1U << 13 | 1U << 12 | 1U << 6;
}

void LCD_K_2(){
//		HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 5  );
//	    HAL_LCD_Write(&hlcd, 2, 0, 1U << 5 );
//	    HAL_LCD_Write(&hlcd, 4, 0, 1U << 12   );
//	    HAL_LCD_Write(&hlcd, 6, 0, 1U << 6   );
//	    HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6 | 1U << 5;
	RAM2 += 1U << 5 ;
	RAM4 += 1U << 12 ;
	RAM6 += 1U << 6 ;
}

void LCD_L_2(){
//		HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 );
//	    HAL_LCD_Write(&hlcd, 2, 0, 1U << 5 | 1U << 6);
//		HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 +=  1U << 6;
	RAM2 += 1U << 5 | 1U << 6;
}

void LCD_M_2(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 13 | 1U << 5);
//	    HAL_LCD_Write(&hlcd, 2, 0, 1U << 13);
//	    HAL_LCD_Write(&hlcd, 4, 0, 1U << 6);
//		HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6 | 1U << 13 | 1U << 5;
	RAM2 += 1U << 13;
	RAM4 += 1U << 6;
}
void LCD_N_2(){
//		HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 13 | 1U << 5);
//	    HAL_LCD_Write(&hlcd, 2, 0, 1U << 13);
//		HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6 | 1U << 13 | 1U << 5;
	RAM2 += 1U << 13;
}

void LCD_O_2(){
	//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 13 | 1U << 5);
	//    HAL_LCD_Write(&hlcd, 2, 0, 1U << 13 | 1U << 6);
	//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6 | 1U << 13 | 1U << 5;
	RAM2 += 1U << 13 | 1U << 6;
}

void LCD_U_2(){
	//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 12  );
	//    HAL_LCD_Write(&hlcd, 2, 0, 1U << 6 | 1U << 13 | 1U << 5);
	//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6 | 1U << 12;
	RAM2 += 1U << 6 | 1U << 13 | 1U << 5;
}

void LCD_P_2(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 5 | 1U << 13|1U << 12);
//	    HAL_LCD_Write(&hlcd, 2, 0, 1U << 5 |  1U << 12);
//		HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6 | 1U << 5 | 1U << 13|1U << 12;
	RAM2 +=  1U << 5 |  1U << 12;
}

void LCD_R_2(){
	//HAL_LCD_Write(&hlcd, 0, 0, 1U << 6 | 1U << 5 | 1U << 13|1U << 12);
	//HAL_LCD_Write(&hlcd, 2, 0, 1U << 5 |  1U << 12);
	//HAL_LCD_Write(&hlcd, 4, 0, 1U << 6);
	//HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6 | 1U << 5 | 1U << 13|1U << 12;
	RAM2 +=  1U << 5 |  1U << 12;
	RAM4 += 1U << 6;
}

void LCD_S_2(){
	RAM0 += 1U << 13 | 1U << 5;
	RAM2 += 1U << 13| 1U << 5 | 1U << 6 |1U << 12;
}

void LCD_T_2(){
//	HAL_LCD_Write(&hlcd, 4, 0, 1U << 6);
//	HAL_LCD_Write(&hlcd, 6, 0, 1U << 12);
//	HAL_LCD_Write(&hlcd, 2, 0, 1U << 12);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM2 += 1U << 12;
	RAM4 += 1U << 6;
	RAM6 += 1U << 12;
}

void LCD_W_2(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 6);
//	HAL_LCD_Write(&hlcd, 2, 0, 1U << 6 | 1U << 13);
//	HAL_LCD_Write(&hlcd, 4, 0, 1U << 6);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 6;
	RAM2 += 1U << 6 | 1U << 13;
	RAM4 += 1U << 6;
}

void LCD_Y_2(){
//	HAL_LCD_Write(&hlcd, 0, 0, 1U << 13 | 1U << 5 | 1U << 12);
 //   HAL_LCD_Write(&hlcd, 2, 0, 1U << 5);
 //   HAL_LCD_Write(&hlcd, 4, 0, 1U << 6);
 //   HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM0 += 1U << 13 | 1U << 5 | 1U << 12;
	RAM2 += 1U << 5;
	RAM4 += 1U << 6;
}

void LCD_Z_2(){
//	HAL_LCD_Write(&hlcd, 2, 0, 1U << 6 | 1U << 12 | 1U << 27);
//	HAL_LCD_Write(&hlcd, 4, 0, 1U << 5 | 1U << 12);
//	HAL_LCD_UpdateDisplayRequest(&hlcd);
	RAM2 += 1U << 6 | 1U << 12 | 1U << 27;
	RAM4 += 1U << 5 | 1U << 12;
}
void LCD_0_2(){
	 RAM0 += 1U << 6|1U << 12;
	 RAM2 += 1U << 12 |1U << 5 |1U << 6|1U << 13;

}
void LCD_1_2(){

	 RAM0 += 1U << 12;
	 RAM2 += 1U << 13;
}
void LCD_2_2(){
	 RAM0 += 1U << 6|1U << 12 |1U << 5|1U << 13;
	 RAM2 += 1U << 12 |1U << 6;
}
void LCD_3_2(){
	 RAM0 += 1U << 12| 1U << 5| 1U << 13;
	 RAM2 += 1U << 13 | 1U << 12| 1U << 6;
}
void LCD_4_2(){
	 RAM0 += 1U << 12| 1U << 5| 1U << 13;
	 RAM2 += 1U << 13 | 1U << 5;
}
void LCD_5_2(){
	RAM0 += 1U << 13 | 1U << 5;
	RAM2 += 1U << 13| 1U << 5 | 1U << 6 |1U << 12;
}
void LCD_6_2(){
	RAM0 += 1U << 6 | 1U << 13 | 1U << 5;
	RAM2 += 1U << 13| 1U << 5 | 1U << 6| 1U << 12;
}
void LCD_7_2(){
	 RAM0 += 1U << 12;
	 RAM2 += 1U << 13| 1U << 12;
}
void LCD_8_2(){
	 RAM0 += 1U << 6|1U << 12|1U << 5|1U << 13;
	 RAM2 += 1U << 12 |1U << 5 |1U << 6|1U << 13;
}
void LCD_9_2(){
	 RAM0 += 1U << 12|1U << 5|1U << 13;
	 RAM2 += 1U << 12 |1U << 5 |1U << 6|1U << 13;
}





void LCD_A_5(){
	RAM0 += 1U << 24 | 1U << 25;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 += 1U << 24| 1U << 25;
	RAM3 += 1U << 2;
}
void LCD_B_5(){
	RAM0 +=  1U << 25;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 +=  1U << 25;
	RAM3 += 1U << 2 | 1U <<3;
}

void LCD_C_5(){
	RAM1 +=  1U << 3;
	RAM2 +=  1U << 24;
	RAM3 += 1U << 2 | 1U <<3;

}

void LCD_D_5(){
	RAM0 +=  1U << 25 | 1U <<24;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 +=  1U << 25;
	RAM3 +=  1U <<3;
}

void LCD_E_5(){
	RAM0 +=  1U << 25;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 +=  1U << 24;
	RAM3 += 1U << 2 | 1U <<3;
}

void LCD_F_5(){
	RAM0 +=  1U << 25;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 +=  1U << 24;
	RAM3 += 1U << 2 ;
}

void LCD_G_5(){
	RAM0 +=  1U << 25;
	RAM1 +=  1U << 3;
	RAM2 +=  1U << 25 | 1U << 24;
	RAM3 += 1U << 2 | 1U <<3;

}

void LCD_H_5(){
	RAM0 +=  1U << 25;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 +=  1U << 25;
	RAM3 += 1U << 2;
}

void LCD_I_5(){
	RAM2 += 1U << 25 | 1U << 24;
}

void LCD_J_5(){
	RAM2 += 1U << 25 | 1U << 24;
	RAM3 += 1U << 3;
}

void LCD_K_5(){
	RAM1 += 1U << 2| 1U << 3;
	RAM3 += 1U << 2 ;
	RAM4 += 1U << 24 ;
	RAM7 += 1U << 3 ;
}

void LCD_L_5(){
	RAM1 +=  1U << 3;
	RAM3 += 1U << 2 | 1U <<3;
}

void LCD_M_5(){
	RAM0 +=  1U << 25;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 +=  1U << 25;
	RAM5 +=  1U << 3;
}
void LCD_N_5(){
	RAM0 +=  1U << 25;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 +=  1U << 25;
}

void LCD_O_5(){
	RAM0 +=  1U << 25;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 +=  1U << 25;
	RAM3 +=  1U << 3;
}

void LCD_U_5(){
	RAM0 +=  1U << 24;
	RAM1 +=  1U << 3;
	RAM2 +=  1U << 25;
	RAM3 +=  1U << 3 | 1U << 2;
}

void LCD_P_5(){
	RAM0 += 1U << 24 | 1U << 25;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 += 1U << 24;
	RAM3 += 1U << 2;
}

void LCD_R_5(){
	RAM0 += 1U << 24 | 1U << 25;
	RAM1 += 1U << 2| 1U << 3;
	RAM2 += 1U << 24;
	RAM3 += 1U << 2;
	RAM5 += 1U << 3;
}

void LCD_S_5(){
	RAM0 +=  1U << 25;
	RAM1 += 1U << 2;
	RAM2 +=  1U << 25 | 1U << 24;
	RAM3 += 1U << 2 | 1U <<3;
}

void LCD_T_5(){
	RAM5 += 1U << 3;
	RAM6 += 1U << 24;
	RAM2 += 1U << 24;

}

void LCD_W_5(){
		RAM1 +=  1U << 3;
		RAM2 +=  1U << 25;
		RAM5 +=  1U << 3;
		RAM3 +=  1U << 3;
}

void LCD_Y_5(){
	RAM5 +=  1U << 3;
	RAM0 +=  1U << 25 | 1U << 24;
	RAM1 +=  1U << 2;
	RAM3 +=  1U << 2;
}

void LCD_Z_5(){
	RAM2 +=  1U << 24;
	RAM3 +=  1U << 3;
	RAM5 +=  1U << 2;
	RAM4 +=  1U << 24;
}

void LCD_0_5(){
	 RAM0 += 1U << 24;
	 RAM1 += 1U << 3 ;
	 RAM2 += 1U << 24 | 1U << 25;
	 RAM3 += 1U << 3 | 1U << 2;

}
void LCD_1_5(){
	RAM0 += 1U << 24;
	RAM2 += 1U << 25;
}
void LCD_2_5(){
	 RAM0 += 1U << 24 | 1U << 25;
	 RAM1 += 1U << 3 | 1U << 2 ;
	 RAM2 += 1U << 24 ;
	 RAM3 += 1U << 3;
}
void LCD_3_5(){
	RAM0 += 1U << 24 | 1U << 25;
	RAM2 += 1U << 25 | 1U << 24 | 1U << 2;
	RAM3 += 1U << 3;

}
void LCD_4_5(){
	RAM0 += 1U << 24 | 1U << 25;
	RAM1 += 1U << 2;
	RAM3 += 1U << 2;
	RAM2 += 1U << 25 | 1U << 2;
}
void LCD_5_5(){
	RAM0 +=  1U << 25;
	RAM1 += 1U << 2;
	RAM2 +=  1U << 25 | 1U << 24;
	RAM3 += 1U << 2 | 1U <<3;
}
void LCD_6_5(){
	RAM0 +=  1U << 25;
	RAM1 += 1U << 2 | 1U << 3;
	RAM2 +=  1U << 25 | 1U << 24;
	RAM3 += 1U << 2 | 1U <<3;
}
void LCD_7_5(){
	RAM0 += 1U << 24;
	RAM2 += 1U << 25 | 1U << 24;
}
void LCD_8_5(){
	RAM0 +=  1U << 25 | 1U << 24;
	RAM1 += 1U << 2 | 1U << 3;
	RAM2 +=  1U << 25 | 1U << 24;
	RAM3 += 1U << 2 | 1U <<3;
}
void LCD_9_5(){
	RAM0 +=  1U << 25 | 1U << 24;
	RAM1 += 1U << 2;
	RAM2 +=  1U << 25 | 1U << 24;
	RAM3 += 1U << 2 | 1U <<3;
}



void LCD_A_6(){
	RAM0 += 1U << 9 | 1U << 26 | 1U << 8 | 1U << 17 ;
	RAM2 += 1U << 9 | 1U << 26 | 1U << 8;
}
void LCD_B_6(){
	RAM0 +=  1U << 26 | 1U << 8 | 1U << 17 ;
	RAM2 +=  1U << 26 | 1U << 8 | 1U << 17;
}

void LCD_C_6(){
	RAM0 +=  1U << 17 ;
	RAM2 +=  1U << 26 | 1U << 17| 1U << 9;

}

void LCD_D_6(){
	RAM0 +=  1U << 26 | 1U << 8 | 1U << 17| 1U << 9 ;
	RAM2 +=  1U << 8 | 1U << 17;
}

void LCD_E_6(){
	RAM0 +=  1U << 26 | 1U << 8 | 1U << 17 ;
	RAM2 +=  1U << 26 | 1U << 9 | 1U << 17;
}

void LCD_F_6(){
	RAM0 +=  1U << 26 | 1U << 8 | 1U << 17 ;
	RAM2 +=  1U << 26 | 1U << 9;
}

void LCD_G_6(){
	RAM0 +=  1U << 8 | 1U << 17 ;
	RAM2 +=  1U << 26 | 1U << 8 | 1U << 17| 1U << 9;

}

void LCD_H_6(){
	RAM0 +=  1U << 26 | 1U << 8 | 1U << 17 ;
	RAM2 +=  1U << 26 | 1U << 8;
}

void LCD_I_6(){
 RAM2 += 1U << 8 | 1U << 9;

}

void LCD_J_6(){
	 RAM2 += 1U << 8 | 1U << 9 | 1U << 17;
}

void LCD_K_6(){
	RAM0 +=  1U << 26 | 1U << 17 ;
	RAM2 +=  1U << 26;
	RAM4 +=  1U << 9;
	RAM6 +=  1U << 17;
}

void LCD_L_6(){
	RAM0 +=  1U << 17;
	RAM2 += 1U << 26 | 1U << 17;
}

void LCD_M_6(){
	RAM0 +=  1U << 26 | 1U << 8 | 1U << 17 ;
	RAM2 += 1U << 8 ;
	RAM4 += 1U << 17 ;
}
void LCD_N_6(){
	RAM0 +=  1U << 26 | 1U << 8 | 1U << 17 ;
	RAM2 += 1U << 8 ;
}

void LCD_O_6(){
	RAM0 +=  1U << 26 | 1U << 8 | 1U << 17 ;
	RAM2 += 1U << 8 | 1U << 17 ;
}

void LCD_U_6(){
	RAM0 +=   1U << 17 | 1U << 9;
	RAM2 += 1U << 8 | 1U << 17 | 1U << 26;
}

void LCD_P_6(){
	RAM0 +=  1U << 26 | 1U << 8 | 1U << 17 | 1U << 9;
	RAM2 +=  1U << 26 | 1U << 9;
}

void LCD_R_6(){
	RAM0 +=  1U << 26 | 1U << 8 | 1U << 17 | 1U << 9;
	RAM2 +=  1U << 26 | 1U << 9;
	RAM6 +=  1U << 17;
}

void LCD_S_6(){
	RAM0 += 1U << 26 | 1U << 8 ;
	RAM2 += 1U << 9 | 1U << 26 | 1U << 8| 1U << 17;
}

void LCD_T_6(){
	RAM4 += 1U << 17;
	RAM6 += 1U << 9;
	RAM2 += 1U << 9;
}

void LCD_W_6(){
	RAM2 += 1U << 17;
	RAM0 += 1U << 17;
	RAM2 += 1U << 8;
	RAM4 += 1U << 17;
}

void LCD_Y_6(){
	RAM4 += 1U << 17;
	RAM0 += 1U << 26 | 1U << 8 | 1U << 9;
	RAM2 += 1U << 26;

}

void LCD_Z_6(){
	RAM2 += 1U << 17 | 1U << 9;
	RAM4 += 1U << 26 | 1U << 9;

}

void LCD_0_6(){
	 RAM0 += 1U << 17 | 1U << 9;
	 RAM2 += 1U << 9 | 1U << 26 | 1U << 17 | 1U << 8;
}
void LCD_1_6(){
	RAM0 += 1U << 9;
	RAM2 += 1U << 8;
}
void LCD_2_6(){
	 RAM0 += 1U << 17 | 1U << 9 | 1U << 26 | 1U << 8;
	 RAM2 += 1U << 9 |  1U << 17;
}
void LCD_3_6(){
	RAM0 += 1U << 9 | 1U << 8 | 1U << 26;
	RAM2 += 1U << 8 | 1U << 9 | 1U << 17;

}
void LCD_4_6(){
	RAM0 += 1U << 9 | 1U << 8 | 1U << 26;
	RAM2 += 1U << 8 | 1U << 26;
}
void LCD_5_6(){
	RAM0 += 1U << 26 | 1U << 8 ;
	RAM2 += 1U << 9 | 1U << 26 | 1U << 8| 1U << 17;
}
void LCD_6_6(){
	 RAM0 += 1U << 17 | 1U << 26 | 1U << 8;
	 RAM2 += 1U << 9 | 1U << 26 | 1U << 17 | 1U << 8;
}
void LCD_7_6(){
	RAM0 += 1U << 9;
	RAM2 += 1U << 8 | 1U << 9;
}
void LCD_8_6(){
	 RAM0 += 1U << 17 | 1U << 26 | 1U << 8 | 1U << 9;
	 RAM2 += 1U << 9 | 1U << 26 | 1U << 17 | 1U << 8;
}
void LCD_9_6(){
	 RAM0 += 1U << 26 | 1U << 8 | 1U << 9;
	 RAM2 += 1U << 9 | 1U << 26 | 1U << 17 | 1U << 8;
}



/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
