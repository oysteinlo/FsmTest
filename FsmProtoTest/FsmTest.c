#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FsmTest.h"



void InitFsmTest(fsmData_t *pFsm)
{
	stateElement_t stateMatrix[NUMOFSTATES][NUMOFEVENTS] =
	{	//eStartReq,								eStarted							eStopReq							eStopped
		{ { eStarting, "Stopped->Starting"},	{ eRunning, "Stopped->Running" },	{ eStopping, "Stopped->Stopping" },		{ eStopped, "Stopped->Stopped" } },//eStopped
		{ { eRunning, "Starting->Running" },	{ eRunning, "Started->Running" },	{ eStopping, "Starting->Stopping" },	{ eStopped, "Starting->Stopped" } },//eStarting
		{ { eRunning, "Running->Running" },		{ eRunning, "Running->Running" },	{ eStopping, "Running->Stopping" },		{ eStopped, "Running->Stopped" } },//eRunning
		{ { eStopping, "Running->Stopping" },	{ eRunning, "Stopping->Running" },	{ eStopping, "Stopping->Stopping" },	{ eStopped, "Stopping->Stopped" } },//eStopping
	};

	pFsm->pTransitionMatrix = calloc(NUMOFSTATES*NUMOFEVENTS, sizeof(stateElement_t));
	memcpy(pFsm->pTransitionMatrix, stateMatrix, NUMOFSTATES*NUMOFEVENTS*sizeof(stateElement_t));

	pFsm->presentState = eStopped;
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