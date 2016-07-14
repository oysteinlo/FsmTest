#pragma once
#include "FsmManager.h"
#include "IoDef.h"

/*****************************************************************
* typedefs
*****************************************************************/

typedef enum stateType{
	eStopped,
	eStarting,
	eRunning,
	eStopping,
	NUMOFSTATES
} state_t;

typedef enum eventType{
	eEvStartReq,
	eEvStarted,
	eEvStopReq,
	eEvStopped,
	eEvTimeout,
	NUMOFEVENTS
} event_t;


void InitFsmTest(fsmData_t *pFsm, inputIo_t *pIn, outputIo_t *pOut);
void RunFsmTest(fsmData_t *pFsm, inputIo_t *pIn);


