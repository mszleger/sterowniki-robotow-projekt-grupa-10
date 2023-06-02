#ifndef INC_RECORD_H_
#define INC_RECORD_H_
#ifdef __cplusplus
 extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "stm32l476g_discovery_audio.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define BUFF_SIZE (uint32_t)2048
#define SAMPLES_RATE 3
#define NOISE_LVL 123

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
 typedef enum
 {
   BUFFER_OFFSET_NONE = 0,
   BUFFER_OFFSET_HALF,
   BUFFER_OFFSET_FULL,
  } RecordBufferOffset_Typedef;
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */
 void AudioRecord_TransferComplete_CallBack(void);
  void AudioRecord_HalfTransfer_CallBack(void);
  void AudioRecord_Error_CallBack(void);
  void Select_sample_rate(int w);
  void micro_init(int sample_choice);
  void record();
  void micro_deinit();
  void NoiseLVL();
/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* INC_RECORD_H_ */

