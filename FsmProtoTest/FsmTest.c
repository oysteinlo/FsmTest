#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FsmTest.h"




void InitFsmTest(fsmData_t *pFsm, inputIo_t *pIn, outputIo_t *pOut)
{
	transElement_t stateMatrix[NUMOFSTATES][NUMOFEVENTS] =
	{			//eStartReq,					eStarted (running)				eStopReq							eStopped
/*eStopped*/	{ { &pIn->startReq, eStarting },{ &pIn->running, eRunning },	{ NULL },						{ NULL	} },			//eStopped
/*eStarting*/	{ { &pIn->startReq, eStarting },{ &pIn->running, eRunning },	{ NULL },						{ NULL, } },			//eStarting
/*eRunning*/	{ { NULL },						{ NULL },						{ &pIn->stopReq, eStopping },	{ NULL, eStopped } },	//eRunning
/*eStopping*/	{ { NULL },						{ NULL },						{ &pIn->stopReq, eStopping },	{ NULL, eStopped } },	//eStopping
	};

	stateElement_t states[NUMOFSTATES] =
	{
/*eStopped*/	{ &pOut->stopped,	"Stopped" },
/*eStarting*/	{ &pOut->startReq,	"Starting" },
/*eRunning*/	{ &pOut->run,		"Running" },
/*eStopping*/	{ &pOut->stopReq,	"Stopping"},
	};

	pFsm->pState = calloc(NUMOFSTATES, sizeof(stateElement_t));
	memcpy(pFsm->pState, states, NUMOFSTATES*sizeof(stateElement_t));

	pFsm->pTransitionMatrix = calloc(NUMOFSTATES*NUMOFEVENTS, sizeof(transElement_t));
	memcpy(pFsm->pTransitionMatrix, stateMatrix, NUMOFSTATES*NUMOFEVENTS*sizeof(transElement_t));

	pFsm->presentState = eStopped;
	pFsm->numEvents = NUMOFEVENTS;
	pFsm->numStates = NUMOFSTATES;
}

void RunFsmTest(fsmData_t *pFsm, inputIo_t *pIn)
{
	// TODO: Any better way of inverting input????
	int stopped = !pIn->running;
	SetTrigger(pFsm, eRunning, eStopped, &stopped);
	SetTrigger(pFsm, eStopping, eStopped, &stopped);

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