#include "record.h"
#include <stdio.h>
#define PROBA 12
//uint16_t recordBuffer[BUFF_SIZE];
uint16_t RecordBuffNoiseLVL[PROBA];
int i = 0;
uint32_t SamplesTab[SAMPLES_RATE] = {BSP_AUDIO_FREQUENCY_48K
		,BSP_AUDIO_FREQUENCY_32K,BSP_AUDIO_FREQUENCY_16K};
uint32_t sample_rate = -1;
int start_recording = RESET;
int AudioRecordExit = RESET;
int AudioRecordNoiseLVLExit = RESET;
static RecordBufferOffset_Typedef  RecordBufferOffset = BUFFER_OFFSET_NONE;


void Select_sample_rate(int w){
	if(w >=0 && w <=2){
		sample_rate = SamplesTab[i];
	}
}

void micro_init(int sample_choice){   // 	TO WYWOLUJE RAZ PRZED WHILE(1) W MAINIE

	Select_sample_rate(sample_choice);

	if(sample_rate == -1){// bez znaczenia bo w init jest wpisane na stale
		sample_rate = BSP_AUDIO_FREQUENCY_48K;
	}

	  /* Initialize audio input */
	  if (BSP_AUDIO_IN_Init(/*BSP_AUDIO_FREQUENCY_8K*/ DEFAULT_AUDIO_IN_FREQ , //8 kHz wpisane na stale
	                        DEFAULT_AUDIO_IN_BIT_RESOLUTION,
	                        DEFAULT_AUDIO_IN_CHANNEL_NBR) != AUDIO_OK)
	  {
		  printf("NIE UDALO SIE ZAINICJALIZOWAC MIKRO \r\n" );
	  }
	  else{
		  printf("INICJALIZACJA SIE UDALA!   \r\n" );
	  }

}

void micro_deinit(){ // TEGO NIGDZIE NIE WYWOLUJE
	  if (BSP_AUDIO_IN_DeInit() != AUDIO_OK)
	  {
		  printf("BRAK DEINIT \r\n");
	  }
	  else{
		  printf("POPRAWNY DE INIT\r\n");
	  }
}

/*void record(){
	   i = 0;
	 AudioRecordExit = RESET;
	  if (BSP_AUDIO_IN_Record((uint16_t*)&RecordBuff[0],
			  BUFF_SIZE) != AUDIO_OK)
	  {
	    //Error_Handler();
	    printf("NIE NAGRYWA SIE  \r\n" );
	  }
	  else{
		  printf("NAGRYWANIE ROZPOCZETE \r\n" );
}


	  while (AudioRecordExit != SET)
	  {
		 // HAL_Delay(1000);
		  //save recorded samples to FLASH
		 // printf("NAGRYWANE PROBKI: %d    i:  %d\r\n", RecordBuff[i], i);
		  i++;
		  HAL_Delay(1);
		  if (i == (BUFF_SIZE - 1)){
			  AudioRecordExit = SET;
		  }
	  }
	  if (BSP_AUDIO_IN_Stop() != AUDIO_OK)
	  {
	   // Error_Handler();
		  printf("nie udalo sie zatrzymac nagrywania \r\n");
	  }
	  else{
		  printf("KONIEC NAGRYWANIA \r\n");
	  }

	  for (i = 0; i < BUFF_SIZE; i++){
		  printf("NAGRANE PROBKI: %d    i:  %d\r\n", RecordBuff[i], i);
		  HAL_Delay(1000);

	  }

}*/
void record() // to wywoluj w petli while
{
 AudioRecordExit = 0;
RecordBufferOffset = BUFFER_OFFSET_NONE;
i = 0;
HAL_Delay(3000);
// callback function pointers
BSP_AUDIO_IN_RegisterCallbacks(AudioRecord_Error_CallBack,AudioRecord_HalfTransfer_CallBack,
                              AudioRecord_TransferComplete_CallBack);
  /* Initialize audio buffers */
  uint16_t recordBuffer[BUFF_SIZE];

  /* Start the audio record */
  if (BSP_AUDIO_IN_Record((uint16_t*)&recordBuffer[0], // to normalnie dziala, nie zwraca bledu
		  BUFF_SIZE) != AUDIO_OK)
  {
	    printf("NIE NAGRYWA SIE  \r\n" );
	  }
	  else{
		  printf("NAGRYWANIE ROZPOCZETE \r\n" );
	  }


  /* Wait for the audio record to complete */
 // HAL_Delay(5000);

  while (AudioRecordExit != SET)
  {
	 // HAL_Delay(1000);
	  //save recorded samples to FLASH
	 // printf("NAGRYWANE PROBKI: %d    i:  %d\r\n", RecordBuff[i], i);
	  i++;
	  HAL_Delay(1);
	  if (i == (BUFF_SIZE - 1)){
		  AudioRecordExit = SET;
	  }
//	  if (RecordBufferOffset == BUFFER_OFFSET_FULL){ // warunek spelniony gdy wykona sie AudioRecord_TransferComplete_CallBack() ale probki sie nie nagrywaja i nie wychodzi z warunku
//		  AudioRecordExit = SET;
//
//	  }
  }

  /* Stop the audio record */
  if (BSP_AUDIO_IN_Stop() != AUDIO_OK)
  {
   // Error_Handler();
    printf("NIE UDALO SIE ZATRZYMAC NAGRYWANIA\r\n");
  }
  else{
	  printf("nagrywanie zatrzymane\r\n");
  }
  HAL_Delay(2000);

  /* Display recorded samples */
  for (uint32_t i = 0; i < BUFF_SIZE; i++)
  {
    printf("NAGRANO: %u  \r\n", recordBuffer[i]);
  //  HAL_Delay(2);
  }


//  printf("NAGRANO: %u  \r\n", recordBuffer[0]);
//  printf("NAGRANO: %u  \r\n", recordBuffer[1]);
//  printf("NAGRANO: %u  \r\n", recordBuffer[2]);
//  printf("NAGRANO: %u  \r\n", recordBuffer[3]);
//  printf("NAGRANO: %u  \r\n", recordBuffer[100]);
//  printf("NAGRANO: %u  \r\n", recordBuffer[200]);
//  printf("NAGRANO: %u  \r\n", recordBuffer[300]);
  HAL_Delay(5000);

}

void AudioRecord_TransferComplete_CallBack(void)
{
  /* Toggle green LED */
  BSP_LED_Toggle(LED5);

  RecordBufferOffset = BUFFER_OFFSET_FULL;
}

void AudioRecord_HalfTransfer_CallBack(void)
{
  RecordBufferOffset = BUFFER_OFFSET_HALF;
}


void AudioRecord_Error_CallBack(void)
{
  /* Stop the program with an infinite loop */
 // Error_Handler();
	printf("BLAD AUDIO ERROR CALLBACK \r\n");
}

void NoiseLVL() { // na to narazie nie patrz bo jak record() nie działa to to tym bardziej nie bedzie dzialac
	AudioRecordNoiseLVLExit = RESET;
	start_recording = RESET;
	int i = 0;
	  if (BSP_AUDIO_IN_Record((uint16_t*)&RecordBuffNoiseLVL[0],
			  BUFF_SIZE) != AUDIO_OK)
	  {
	    Error_Handler();
	  }

	  while (AudioRecordNoiseLVLExit != SET)
	  {
		  if(RecordBuffNoiseLVL[i] > NOISE_LVL){
			  AudioRecordNoiseLVLExit = SET;
			  start_recording = SET;
		  }
		  if (i == (BUFF_SIZE - 1) ){
			  i = 0;
		  }
		  i++;
	  }

	  if (BSP_AUDIO_IN_Stop() != AUDIO_OK)
	  {
	    Error_Handler();
	  }

	  if (start_recording){
		  record();
	  }
}
