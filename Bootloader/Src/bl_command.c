#include "bl_command.h"

#include "stm32f1xx_hal.h"
#include "usart.h"

static COMMAND_RET (reboot)(void);
static COMMAND_RET (downloadApp)(void);
static COMMAND_RET (doanloadAndRunApp)(void);
static COMMAND_RET (runApp)(void);

char reboot_description[] = "0: reboot system\r\n";
char downloadApp_description[] = "1: download App with xmoderm transfer\r\n";
char runApp_description[] = "2: jump to App\r\n";
char doanloadAndRunApp_description[] = "3: download App and jump to App\r\n";

static Cmd CmdArray[COMMAND_MAX] = {
	{reboot, reboot_description},
	{downloadApp, downloadApp_description},
	{runApp, runApp_description},
	{doanloadAndRunApp, doanloadAndRunApp_description}
};

//display all suppoted command
void commandAllDisplay(void)
{
	uint8_t i;
	for (i = 0; i < COMMAND_MAX; ++i)
	{
		MainComm_SendString(CmdArray[0].description);
//		MainComm_SendString("1: download App with xmoderm transfer\r\n");
	}
}

//execute seleted command
COMMAND_RET commandRun(Cmd const *cmd)
{
	return cmd->func();
}

//get a command
Cmd const *  commandGet(COMMAND command)
{
	if(command >= COMMAND_MAX)
	{
		MainComm_Error("unknown command\r\n");
		return NULL;
	}
	return (CmdArray+command);
}

//display selected command
void commmandSelectedDisplay(Cmd *cmd)
{
	if(cmd == NULL)
		MainComm_Error("unkown command\r\n");
	MainComm_SendString(cmd->description);
}


static COMMAND_RET (reboot)(void)
{
	HAL_NVIC_SystemReset();
	return COMMAND_SUCCESS;
}

static COMMAND_RET (downloadApp)(void)
{
	//xmoderm transfer
	return COMMAND_SUCCESS;
}

static COMMAND_RET (doanloadAndRunApp)(void)
{
	downloadApp();
	runApp();
	return COMMAND_SUCCESS;
}
	
	
static COMMAND_RET (runApp)(void)
{
	return COMMAND_SUCCESS;
}