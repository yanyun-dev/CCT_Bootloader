#include "bl_command.h"

#include "stm32f1xx_hal.h"
#include "usart.h"

static COMMAND_RET (reboot)(void);
static COMMAND_RET (downloadApp)(void);
static COMMAND_RET (doanloadAndRunApp)(void);
static COMMAND_RET (runApp)(void);

static Cmd CmdArray[COMMAND_MAX] = {
	{reboot, "  0: reboot system\r\n"},
	{downloadApp, "  1: download App with xmoderm transfer\r\n"},
	{runApp, "  2: jump to App\r\n"},
	{doanloadAndRunApp, "  3: download App and jump to App\r\n"}
};

//display all suppoted command
void commandAllDisplay(void)
{
	uint8_t i;
	MainComm_SendString("Supported command list:\r\n");
	for (i = 0; i < COMMAND_MAX; ++i)
	{
		MainComm_SendString(CmdArray[i].description);
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
	MainComm_SendString("reboot!!!\r\n");
	HAL_NVIC_SystemReset();
	return COMMAND_SUCCESS;
}

static COMMAND_RET (downloadApp)(void)
{
	//xmoderm transfer
	MainComm_SendString("download app sucess!\r\n");
	return COMMAND_SUCCESS;
}

static COMMAND_RET (doanloadAndRunApp)(void)
{
	downloadApp();
	runApp();
	MainComm_SendString("download app sucess and run!\r\n");
	return COMMAND_SUCCESS;
}
	
	
static COMMAND_RET (runApp)(void)
{
	MainComm_SendString("run app!\r\n");
	return COMMAND_SUCCESS;
}