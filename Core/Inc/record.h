#ifndef INC_RECORD_H_
#define INC_RECORD_H_
#ifdef __cplusplus
 extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "dfsdm.h"
#include "lcd.h"
#include "stm32l476g_discovery_audio.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define BUFF_NOISE_SIZE 2048
#define SaturaLH(N, L, H) (((N)<(L))?(L):(((N)>(H))?(H):(N)))
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */
void record(int32_t *buffer, int buffsize);
  int NoiseLVL();
  int abs(int num);
/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* INC_RECORD_H_ */

