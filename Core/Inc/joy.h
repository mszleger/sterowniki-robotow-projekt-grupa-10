/*
 * joy.h
 *
 *
 *
 */

#ifndef INC_JOY_H_
#define INC_JOY_H_
#ifdef __cplusplus
 extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern struct joy{
 	int tick_center;
 	int tick_left;
 	int tick_right;
 	int tick_up;
 	int tick_down;

 	int get_tick_center;
 	int get_tick_up;
 	int get_tick_down;
 	int get_tick_left;
 	int get_tick_right;

 	int tab[16384];
 	int ind;
 };

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */
void joy_init(struct joy* joystick);
void joy_up(struct joy* joystick);
void joy_down(struct joy* joystick);
void joy_left(struct joy* joystick);
void joy_right(struct joy* joystick);
void joy_center(struct joy* joystick);
/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* INC_JOY_H_ */
