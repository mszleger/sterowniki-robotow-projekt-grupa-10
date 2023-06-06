#include "record.h"
#include <stdio.h>
#define PROBA 12

int abs(int num) {
  if (num < 0)
    return -num;
  else
    return num;
}

void record(int32_t *buffer, int buffsize) {
	  if(HAL_DFSDM_FilterRegularStart(&hdfsdm1_filter0) != HAL_OK) {
		  printf("DFSDM: Error starting recording\r\n");
		  return;
	  }
	  for(uint32_t i = 0; i < buffsize; ++i)
		  buffer[i] = HAL_DFSDM_FilterGetRegularValue(&hdfsdm1_filter0, &hdfsdm1_channel2);
	  if(HAL_DFSDM_FilterRegularStop(&hdfsdm1_filter0) != HAL_OK) {
		  printf("DFSDM: Error stopping recording\r\n");
		  return;
	  }
}

int NoiseLVL(){
	int32_t  RecNoiseBuff[BUFF_NOISE_SIZE];
	start_recording(RecNoiseBuff, BUFF_NOISE_SIZE);
	HAL_Delay(3000);
	int t = 0;
	int exit = 0;
	while(!exit){

	for(int i = BUFF_NOISE_SIZE/2; i < BUFF_NOISE_SIZE - 1; i++){
		int avg = abs(SaturaLH((RecNoiseBuff[i] >> 8), -32768, 32767)) + abs(SaturaLH((RecNoiseBuff[i-1] >> 8), -32768, 32767)) + abs(SaturaLH((RecNoiseBuff[i-2] >> 8), -32768, 32767)) + abs(SaturaLH((RecNoiseBuff[i-3] >> 8), -32768, 32767)) + abs(SaturaLH((RecNoiseBuff[i-4] >> 8), -32768, 32767)) + abs(SaturaLH((RecNoiseBuff[i-5] >> 8), -32768, 32767)) + abs(SaturaLH((RecNoiseBuff[i-6] >> 8), -32768, 32767))+ abs(SaturaLH((RecNoiseBuff[i-7] >> 8), -32768, 32767))+ abs(SaturaLH((RecNoiseBuff[i-8] >> 8), -32768, 32767))+ abs(SaturaLH((RecNoiseBuff[i-9] >> 8), -32768, 32767));
		int avg2 = avg / 10;

		if( t >=300 ){ // czekamy okolo 3 przed porownaniem, te delaye sa po to zeby nie wykrywal wcisniecia przycisku jako przekroczenia progu
		if (avg2 > 350){
		//	printf("PRZEKROCZONO PROG \r\n");
			stop_recording();
			return 1;
		}
		else{
		//	printf("ponizej progu \r\n");
		}
		}

		HAL_Delay(10);
		t++;
		if( t == 1000){ // trwa okolo 10 sekund
			exit = 1;
			break;
		}

	}
	}
	//printf("koniec sprawdzania  \r\n");
	stop_recording();
	return 0;
}



























