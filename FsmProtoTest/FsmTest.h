#pragma once
#include "FsmManager.h"

/*****************************************************************
* typedefs
*****************************************************************/

typedef enum stateType{
	eStopped,
	eStarting,
	eRunning,
	eStopping,
	NUMOFSTATES
} state;

typedef enum eventType{
	eEvStartReq,
	eEvStarted,
	eEvStopReq,
	eEvStopped,
	NUMOFEVENTS
} event;




// General functions
void stateEval(fsmData_t *pFsm);
//void exit(int status);
void getIOValues(void);


void InitFsmTest(fsmData_t *pFsm);
void RunFsmTest(fsmData_t *pFsm);


