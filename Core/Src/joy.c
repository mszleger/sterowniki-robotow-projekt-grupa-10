/*
 * joy.c
 *
 *
 *
 */


#include "joy.h"
#include "gpio.h"
#include <stdio.h>

struct joy joystick;

void joy_init(struct joy* joystick){
	joystick->tick_center = 0;
	joystick->tick_left = 0;
	joystick->tick_right = 0;
	joystick->tick_up = 0;
	joystick->tick_down = 0;

	joystick->get_tick_center = 1;
	joystick->get_tick_up = 1;
	joystick->get_tick_down = 1;
	joystick->get_tick_left = 1;
	joystick->get_tick_right = 1;

	joystick->ind = 0;

	for (int i = 0; i < 16384; i++){
		joystick->tab[i] = -1;
	}
}

void joy_up(struct joy* joystick){
	 if(joystick->get_tick_up){
		 joystick->tick_up = HAL_GetTick();
	 }

	  if(HAL_GPIO_ReadPin(GPIOA, JOY_UP_Pin) == GPIO_PIN_SET || joystick->get_tick_up == 0){ /* GORA --> dajemy 0  */
		  joystick->get_tick_up = 0;
	  	 if(HAL_GetTick() - joystick->tick_up >= 25){
	  	   if(HAL_GPIO_ReadPin(GPIOA, JOY_UP_Pin) == GPIO_PIN_SET){
	  		joystick->get_tick_up = 1;
	  		joystick->tab[joystick->ind] = 0;
	  		joystick->ind++;
	  	   while(HAL_GPIO_ReadPin(GPIOA, JOY_UP_Pin) == GPIO_PIN_SET){
	  	   	   	   }
	  	   	   }
	  	     }
	  	   }

}


void joy_down(struct joy* joystick){
	 if(joystick->get_tick_down){
		 joystick->tick_down = HAL_GetTick();
		 }

	  if(HAL_GPIO_ReadPin(GPIOA, JOY_DOWN_Pin) == GPIO_PIN_SET || joystick->get_tick_down == 0){ /* DOL --> dajemy 2 */
		  joystick->get_tick_down = 0;
	  	 if(HAL_GetTick() - joystick->tick_down >= 25){
	  	   if(HAL_GPIO_ReadPin(GPIOA, JOY_DOWN_Pin) == GPIO_PIN_SET){
	  		joystick->get_tick_down = 1;
	  		joystick->tab[joystick->ind] = 2;
	  		joystick->ind++;
	  	   while(HAL_GPIO_ReadPin(GPIOA, JOY_DOWN_Pin) == GPIO_PIN_SET){
	  	   	   	   }
	  	   	   }
	  	     }
	  	   }
}

void joy_right(struct joy* joystick){
	 if(joystick->get_tick_right){
		 joystick->tick_right = HAL_GetTick();
	 }

	  if(HAL_GPIO_ReadPin(GPIOA, JOY_RIGHT_Pin) == GPIO_PIN_SET || joystick->get_tick_right == 0){ /* PRAWO --> dajemy 1 */
		  joystick->get_tick_right = 0;
	  	 if(HAL_GetTick() - joystick->tick_right >= 25){
	  	   if(HAL_GPIO_ReadPin(GPIOA, JOY_RIGHT_Pin) == GPIO_PIN_SET){
	  		joystick->get_tick_right = 1;
	  		joystick->tab[joystick->ind] = 1;
	  		joystick->ind++;
	  	   while(HAL_GPIO_ReadPin(GPIOA, JOY_RIGHT_Pin) == GPIO_PIN_SET){
	  	   	   	   }
	  	   	   }
	  	     }
	  	   }
}

void joy_left(struct joy* joystick){
	 if(joystick->get_tick_left){
		 joystick->tick_left = HAL_GetTick();
	 }

	  if(HAL_GPIO_ReadPin(GPIOA, JOY_LEFT_Pin) == GPIO_PIN_SET || joystick->get_tick_left == 0){ /* LEWO --> dajemy 3 */
		  joystick->get_tick_left = 0;
	  	 if(HAL_GetTick() - joystick->tick_left >= 25){
	  	   if(HAL_GPIO_ReadPin(GPIOA, JOY_LEFT_Pin) == GPIO_PIN_SET){
	  		joystick->get_tick_left = 1;
	  		joystick->tab[joystick->ind] = 3;
	  		joystick->ind++;
	  	   while(HAL_GPIO_ReadPin(GPIOA, JOY_LEFT_Pin) == GPIO_PIN_SET){
	  	   	   	   }
	  	   	   }
	  	     }
	  	   }
}

void joy_center(struct joy* joystick){

	 if(joystick->get_tick_center){
		 joystick->tick_center = HAL_GetTick();
	 }

	  if(HAL_GPIO_ReadPin(GPIOA, JOY_CENTER_Pin) == GPIO_PIN_SET || joystick->get_tick_center == 0){ /* SRODEK --> dajemy 4 */
		  joystick->get_tick_center = 0;
	  	 if(HAL_GetTick() - joystick->tick_center >= 25){
	  	   if(HAL_GPIO_ReadPin(GPIOA, JOY_CENTER_Pin) == GPIO_PIN_SET){
	  		joystick->get_tick_center = 1;
	  		joystick->tab[joystick->ind] = 4;
	  		joystick->ind++;
	  	   while(HAL_GPIO_ReadPin(GPIOA, JOY_CENTER_Pin) == GPIO_PIN_SET){
	  	   	   	   }
	  	   	   }
	  	     }
	  	   }
}



