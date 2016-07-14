#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FsmTest.h"

static void UnexpectedStart(fsmData_t *pFsm);
static void UnexpectedStop(fsmData_t *pFsm);

void InitFsmTest(fsmData_t *pFsm, inputIo_t *pIn, outputIo_t *pOut)
{
	/* Setting state information */
	stateElement_t states[NUMOFSTATES] =
	{
		{ &pOut->stopped,	"Stopped" },					/*eStopped*/
		{ &pOut->startReq,	"Starting", &pIn->timeout },	/*eStarting*/
		{ &pOut->run,		"Running" },					/*eRunning*/
		{ &pOut->stopReq,	"Stopping", &pIn->timeout },	/*eStopping*/
	};

	pFsm->pState = calloc(NUMOFSTATES, sizeof(stateElement_t));
	memcpy(pFsm->pState, states, NUMOFSTATES*sizeof(stateElement_t));

	/* Setting transition information */
	transElement_t stateMatrix[NUMOFSTATES][NUMOFEVENTS] =
	{			
		{	/*eStopped*/
			{ DigNorm, &pIn->startReq, eStarting },					/*eEvStartReq*/
			{ DigNorm, &pIn->running, eRunning, UnexpectedStart },	/*eEvStarted*/
		},			
		{	/*eStarting*/
			{ DigNorm, &pIn->startReq, eStarting },					/*eEvStartReq*/
			{ DigNorm, &pIn->running, eRunning },					/*eEvStarted*/
			{ DigNorm, &pIn->stopReq, eStopping },					/*eEvStopReq*/
			{ Timer, &pFsm->pState[eStarting], eStopped },			/*eEvTimeout*/
		},
		{	/*eRunning*/ 
			{ DigNorm, &pIn->stopReq, eStopping },					/*eEvStopReq*/
			{ DigInv, &pIn->running, eStopped, UnexpectedStop },	/*eEvStopped*/
		},	
		{	/*eStopping*/ 
			{ DigNorm, &pIn->stopReq, eStopping },					/*eEvStopReq*/
			{ DigInv, &pIn->running, eStopped },					/*eEvStopped*/
			{ Timer, &pFsm->pState[eStopping], eRunning },			/*eEvTimeout*/
		},
	};

	pFsm->pTransitionMatrix = calloc(NUMOFSTATES*NUMOFEVENTS, sizeof(transElement_t));
	memcpy(pFsm->pTransitionMatrix, stateMatrix, NUMOFSTATES*NUMOFEVENTS*sizeof(transElement_t));

	pFsm->presentState = eStopped;
	pFsm->numEvents = NUMOFEVENTS;
	pFsm->numStates = NUMOFSTATES;
}

void RunFsmTest(fsmData_t *pFsm, inputIo_t *pIn)
{
	StateEval(pFsm);	/* Evaluate state and events + run generic part*/

	switch (pFsm->presentState)
	{
	case eStopped:
		if (pFsm->enter)
		{ 
			printf("Enter eStopped\n");
		}
		printf("Doing eStopped\n");

		break;
	case eStarting:
		if (pFsm->enter)
		{
			printf("Enter eStarting\n");
		}
		printf("Doing eStarting\n");

		break;
	case eRunning:
		if (pFsm->enter)
		{
			printf("Enter eRunning\n");
		}
		printf("Doing eRunning\n");

		break;
	case eStopping:
		if (pFsm->enter)
		{
			printf("Enter eStopping\n");
		}
		printf("Doing eStopping\n");

		break;
	default:
		printf("Illegal state\n");
	}
}

static void UnexpectedStart(fsmData_t *pFsm)
{
	printf("UnexpectedStart-%d\n", pFsm->presentState);
}

static void UnexpectedStop(fsmData_t *pFsm)
{
	printf("UnexpectedStop-%d\n", pFsm->presentState);
}