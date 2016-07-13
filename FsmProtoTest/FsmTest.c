#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FsmTest.h"




void InitFsmTest(fsmData_t *pFsm, inputIo_t *pIn, outputIo_t *pOut)
{
	transElement_t stateMatrix[NUMOFSTATES][NUMOFEVENTS] =
	{			//eStartReq,					eStarted (running)				eStopReq							eStopped
/*eStopped*/	{ { eStarting, &pIn->startReq},	{ eRunning, &pIn->running },	{ eStopping, NULL },			{ eStopped, NULL } },//eStopped
/*eStarting*/	{ { eStarting, NULL },			{ eRunning, &pIn->running },	{ eStopping, &pIn->stopReq },	{ eStopped, &pIn->stopped } },//eStarting
/*eRunning*/	{ { eRunning, NULL },			{ eRunning, NULL },				{ eStopping, &pIn->stopReq },	{ eStopped, &pIn->stopped } },//eRunning
/*eStopping*/	{ { eStarting, NULL },			{ eRunning, &pIn->running },	{ eStopping, NULL },			{ eStopped, &pIn->stopped } },//eStopping
	};

	stateElement_t states[NUMOFSTATES] =
	{
/*eStopped*/	{ &pOut->stopped, "Stopped" },
/*eStarting*/	{ &pOut->startReq, "Starting" },
/*eRunning*/	{ &pOut->run, "Running" },
/*eStopping*/	{ &pOut->stopReq, "stopped"},
	};

	pFsm->pState = calloc(NUMOFSTATES, sizeof(stateElement_t));
	memcpy(pFsm->pState, states, NUMOFSTATES*sizeof(stateElement_t));

	pFsm->pTransitionMatrix = calloc(NUMOFSTATES*NUMOFEVENTS, sizeof(transElement_t));
	memcpy(pFsm->pTransitionMatrix, stateMatrix, NUMOFSTATES*NUMOFEVENTS*sizeof(transElement_t));

	pFsm->presentState = eStopped;
	pFsm->numEvents = NUMOFEVENTS;
	pFsm->numStates = NUMOFSTATES;
}

void RunFsmTest(fsmData_t *pFsm)
{
	stateEval(pFsm);

	switch (pFsm->presentState)
	{
	case eStopped:
		if (pFsm->enter)
		{ 
			printf("Enter eStopped\n");
		}
		printf("Doing eStopped\n");

		if (pFsm->exit)
		{
			printf("Exit eStopped\n");
		}
		break;
	case eStarting:
		if (pFsm->enter)
		{
			printf("Enter eStarting\n");
		}
		printf("Doing eStarting\n");

		if (pFsm->exit)
		{
			printf("Exit eStarting\n");
		}
		break;
	case eRunning:
		if (pFsm->enter)
		{
			printf("Enter eRunning\n");
		}
		printf("Doing eRunning\n");

		if (pFsm->exit)
		{
			printf("Exit eRunning\n");
		}
		break;
	case eStopping:
		if (pFsm->enter)
		{
			printf("Enter eStopping\n");
		}
		printf("Doing eStopping\n");

		if (pFsm->exit)
		{
			printf("Exit eStopping\n");
		}		break;
	}
}