#ifndef __BL_COMMAND_H
#define __BL_COMMAND_H


typedef enum {
	COMMAND_SUCCESS,
	COMMAND_FAILURE
} COMMAND_RET;

typedef enum {
	REBOOT,
	DOWNLOAD_APP,
	RUN_APP,
	DOWNLOAD_AND_RUN_APP,
	COMMAND_MAX
} COMMAND;

typedef COMMAND_RET (*CMD_Func)(void);

typedef struct CMD Cmd;
struct CMD {
	const CMD_Func func;
	char * description;
};

//display all suppoted command
void commandAllDisplay(void);

//display selected command
void commmandSelectedDisplay(Cmd *cmd);

//execute seleted command
COMMAND_RET commandRun(Cmd const *cmd);

//get a command
Cmd const *  commandGet(COMMAND command);

#endif