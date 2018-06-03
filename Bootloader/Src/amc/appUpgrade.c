#include "appUpgrade.h"
#include "usart.h"


	
	void flash_program(uint32_t * pData, uint32_t size)
	{
		static uint16_t positionInPage = 0;
		static	FLASH_EraseInitTypeDef FLASH_EraseInitStructure = {FLASH_TYPEERASE_PAGES, FLASH_BANK_1, 0x08000000 + APP_Start_Page_Address * 1024, 1};	
		uint32_t pageError;
		uint32_t i;
		HAL_FLASH_Unlock();
		for(i = 0; i < size; ++i)
		{
			if(!positionInPage)
			{
				HAL_FLASHEx_Erase(&FLASH_EraseInitStructure, &pageError);
				if(pageError != 0xFFFFFFFF)
				{
					while(1);
				}
			}
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_EraseInitStructure.PageAddress + positionInPage, pData[i]) == HAL_OK)
			{
				positionInPage += 4;
				if(positionInPage == FLASH_PAGE_SIZE)
				{
					positionInPage = 0;
					FLASH_EraseInitStructure.PageAddress += FLASH_PAGE_SIZE;
				}
			}
			else
			{
				DebugComm_SendErrorString("Flash programming error!!!\r\n");
			}
		}
		HAL_FLASH_Lock();
	}