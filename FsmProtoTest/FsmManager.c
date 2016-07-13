#include <stdio.h>
#include "FsmManager.h"

void stateEval(fsmData_t *pFsm)
{
	int i;
	

	//determine the State-Matrix-Element in dependany of current state and triggered event
	pFsm->enter = 0;
	
	for (i = 0; i < pFsm->numEvents; i++)
	{
		transElement_t *pTransition = pFsm->pTransitionMatrix + (pFsm->presentState*pFsm->numEvents + i);
		
		if (pTransition->pTrigger)
		{
			if (*pTransition->pTrigger)
			{
				if (pFsm->presentState != pTransition->nextState)
				{
					pFsm->enter = 1;
					printf("Next state %s\n", pFsm->pState[pTransition->nextState].name);
				}
				pFsm->presentState = pTransition->nextState;
				break;
			}
		}
	}

	/* Set output according to mapped IO*/
	for (i = 0; i < pFsm->numStates; i++)
	{
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
	}

	//if (pFsm->presentState != pTransition->nextState)
	//{ 
	//	pFsm->enter = 1;
	//	pFsm->presentState = pTransition->nextState;
	//}
	//else
	//{
	//	pFsm->enter = 0;
	//}
	

	//do the transition to the next state (set requestet next state to current state)...
	
	//... and fire the proper action
//	(*stateEvaluation.actionToDo)();
	
}
