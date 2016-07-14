#include <stdio.h>
#include "FsmManager.h"

void StateEval(fsmData_t *pFsm)
{
	int i;

	/* Check all events and set next state*/
	pFsm->enter = 0;
	for (i = 0; i < pFsm->numEvents; i++)
	{
		/* Little trick as I could not define double array, size is only known runtime. Generic part should not kbow anything about the specific state machine*/
		transElement_t *pTransition = pFsm->pTransitionMatrix + (pFsm->presentState*pFsm->numEvents + i);
		
		if (pTransition->funcGuard)
		{
			if (pTransition->funcGuard(pTransition->pTrigger))
			{
				if (pFsm->presentState != pTransition->nextState)
				{
					pFsm->presentState = pTransition->nextState;
					pFsm->enter = 1;
					SetStateTimer(&pFsm->pState[pFsm->presentState]);
					printf("Next state %s\n", pFsm->pState[pTransition->nextState].name);
				}				
			}
		}
	}

	
	for (i = 0; i < pFsm->numStates; i++)
	{
		/* Set output according to mapped IO*/
		if (pFsm->pState[i].pOutput == NULL)
		{
			break;
		}
		if (pFsm->presentState == i)
		{
			*pFsm->pState[i].pOutput = 1;
		}
		else
		{
			*pFsm->pState[i].pOutput = 0;
		}

		/* Update timer*/
		if (pFsm->pState[i].timer > 0)
		{
			pFsm->pState[i].timer--;
		}
	}
	
	//... and fire the proper action
	//	(*stateEvaluation.actionToDo)();
	
}

void SetTrigger(fsmData_t *pFsm, state_t st, event_t ev, int *pVal)
{
	transElement_t *pTransition = pFsm->pTransitionMatrix + (st*pFsm->numEvents + ev);

	//pTransition->pTrigger = pVal;
}

void SetStateTimer(stateElement_t *pState)
{
	if (pState->pTimeout != NULL)
	{
		pState->timer = *pState->pTimeout;
	}
}


int DigNorm(int *pInp)
{
	return *pInp;
}

int DigInv(int *pInp)
{
	return !*pInp;
}

int Timer(stateElement_t *state)
{
	return state->timer <= 0;
}

int DigIo(struct terminal *term)
{
	return 1;
}