#include "bl_command.h"

#include "stm32f1xx_hal.h"
#include "usart.h"
#include "xmodem.h"

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
	DebugComm_SendString("Supported command list:\r\n");
	for (i = 0; i < COMMAND_MAX; ++i)
	{
		DebugComm_SendString(CmdArray[i].description);
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
		DebugComm_SendErrorString("unknown command\r\n");
		return NULL;
	}
	return (CmdArray+command);
}

//display selected command
void commmandSelectedDisplay(Cmd *cmd)
{
	if(cmd == NULL)
		DebugComm_SendErrorString("unkown command\r\n");
	DebugComm_SendString(cmd->description);
}


static COMMAND_RET (reboot)(void)
{
	DebugComm_SendString("reboot!!!\r\n");
	HAL_NVIC_SystemReset();
	return COMMAND_SUCCESS;
}

static COMMAND_RET (downloadApp)(void)
{
	static uint8_t xbuff[1030];	
	int32_t rcvSize;
	uint8_t ctrlChar, c, errorCounter = 0;
	//xmoderm transfer
	DebugComm_SendString("download app start!\r\n");
	rcvSize = xmodemReceive(xbuff, sizeof(xbuff));
	if(rcvSize > 0)
		DebugComm_SendData(xbuff, rcvSize, 1000);
	else if(rcvSize == -1)
	{
		DebugComm_SendErrorString("Canceled!!!\r\n");
		goto fail;
	}
	else if(rcvSize == -2)
	{
		DebugComm_SendErrorString("Sync error!!!\r\n");
		goto fail;
	}
	else if(rcvSize == -3)
	{
		DebugComm_SendErrorString("too many retry error!!!\r\n");
		goto fail;
	}
	DebugComm_SendString("download app complete!\r\n");
	return COMMAND_SUCCESS;
	
	fail:
	return COMMAND_FAILURE;
}

static COMMAND_RET (doanloadAndRunApp)(void)
{
	downloadApp();
	runApp();
	DebugComm_SendString("download app sucess and run!\r\n");
	return COMMAND_SUCCESS;
}
	
	
static COMMAND_RET (runApp)(void)
{
	DebugComm_SendString("run app!\r\n");
	return COMMAND_SUCCESS;
}