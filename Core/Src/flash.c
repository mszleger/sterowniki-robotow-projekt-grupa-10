#include "flash.h"

static void     Fill_Buffer (uint8_t *pBuffer, uint32_t uwBufferLength, uint32_t uwOffset);
static uint8_t  Buffercmp   (uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);

void QSPI_demo (void)
{
  /* QSPI info structure */
  static QSPI_Info pQSPI_Info;
  uint8_t status;
  __IO uint8_t *data_ptr;
  uint32_t index;

  /*##-1- Configure the QSPI device ##########################################*/
  /* QSPI device configuration */
  status = BSP_QSPI_Init();

  if (status != QSPI_OK)
  {
    printf("QSPI Initialization : FAILED.\n\r");
  }
  else
  {
    /*##-2- Read & check the QSPI info #######################################*/
    /* Initialize the structure */
    pQSPI_Info.FlashSize          = (uint32_t)0x00;
    pQSPI_Info.EraseSectorSize    = (uint32_t)0x00;
    pQSPI_Info.EraseSectorsNumber = (uint32_t)0x00;
    pQSPI_Info.ProgPageSize       = (uint32_t)0x00;
    pQSPI_Info.ProgPagesNumber    = (uint32_t)0x00;

    /* Read the QSPI memory info */
    BSP_QSPI_GetInfo(&pQSPI_Info);

    /* Test the correctness */
    if((pQSPI_Info.FlashSize != 0x1000000) || (pQSPI_Info.EraseSectorSize != 0x1000)  ||
       (pQSPI_Info.ProgPageSize != 0x100)  || (pQSPI_Info.EraseSectorsNumber != 4096) ||
       (pQSPI_Info.ProgPagesNumber != 65536))
    {
      printf("QSPI GET INFO : FAILED.\n\r");
    }
    else
    {
      /*##-3- Erase QSPI memory ################################################*/
      if(BSP_QSPI_Erase_Block(WRITE_READ_ADDR) != QSPI_OK)
      {
        printf("QSPI ERASE : FAILED.\n\r");
      }
      else
      {
        /*##-4- QSPI memory read/write access  ###############################*/
        /* Fill the buffer to write */
        Fill_Buffer(qspi_aTxBuffer, BUFFER_SIZE, 0xD20F);

        /* Write data to the QSPI memory */
        if(BSP_QSPI_Write(qspi_aTxBuffer, WRITE_READ_ADDR, BUFFER_SIZE) != QSPI_OK)
        {
          printf("QSPI WRITE : FAILED.\n\r");
        }
        else
        {
          /* Read back data from the QSPI memory */
          if(BSP_QSPI_Read(qspi_aRxBuffer, WRITE_READ_ADDR, BUFFER_SIZE) != QSPI_OK)
          {
            printf("QSPI READ : FAILED.\n\r");
          }
          else
          {
            /*##-5- Checking data integrity ##################################*/
            if(Buffercmp(qspi_aRxBuffer, qspi_aTxBuffer, BUFFER_SIZE) > 0)
            {
              printf("QSPI COMPARE : FAILED\n\r");
            }
            else
            {
              /*##-6- QSPI memory in memory-mapped mode#######################*/
              if(BSP_QSPI_EnableMemoryMappedMode() != QSPI_OK)
              {
            	  printf("QSPI MEMORY-MAPPED CFG : FAILED.\n\r");
              }
              else
              {
                for(index = 0, data_ptr = (__IO uint8_t *)(QSPI_BASE_ADDR + WRITE_READ_ADDR);
                    index < BUFFER_SIZE; index++, data_ptr++)
                {
                  if(*data_ptr != qspi_aTxBuffer[index])
                  {
                	  printf("QSPI MEMORY-MAPPED ACCESS : FAILED.\n\r");
                    break;
                  }
                }

                if(index == BUFFER_SIZE)
                {
                	printf("QSPI Test OK.\r\n");
                }
              }
            }
          }
        }
      }
    }
  }

}

static void Fill_Buffer(uint8_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset)
{
  uint32_t tmpIndex = 0;

  /* Put in global buffer different values */
  for (tmpIndex = 0; tmpIndex < uwBufferLenght; tmpIndex++ )
  {
    pBuffer[tmpIndex] = tmpIndex + uwOffset;
  }
}

static uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}


















HAL_StatusTypeDef Flash_Init(void) {
	while(1);
}

HAL_StatusTypeDef Flash_Test(void) {
	while(1);
}

HAL_StatusTypeDef Flash_Read(uint32_t start_address, uint8_t* buffer, uint32_t buffer_length) {
	while(1);
}

HAL_StatusTypeDef Flash_Write(uint32_t start_address, uint8_t* buffer, uint32_t buffer_length) {
	while(1);
}

HAL_StatusTypeDef Flash_Track_Status_Set(uint8_t track_number, uint8_t new_track_status) {
	while(1);
}

HAL_StatusTypeDef Flash_Track_Status_Get(uint8_t track_number, uint8_t* track_status) {
	while(1);
}

HAL_StatusTypeDef Flash_Record_Start(uint8_t track_number) {
	while(1);
}

HAL_StatusTypeDef Flash_Record_Save_Buffer(uint8_t* buffer, uint32_t buffer_length) {
	while(1);
}

HAL_StatusTypeDef Flash_Play_Start(uint8_t track_number) {
	while(1);
}

HAL_StatusTypeDef Flash_Play_Read_Buffer(uint8_t* buffer, uint32_t buffer_length) {
	while(1);
}















































