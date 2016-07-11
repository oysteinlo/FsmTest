#include "FsmManager.h"

void stateEval(fsmData_t *pFsm)
{
	int s = 4;
	//unsigned int array[ 100 ][ 150 ];
	//unsigned int(*array)[150] = (unsigned int(*)[150]) ptr;
	
	stateElement_t (*pStateMatrix)[4] = (stateElement_t(*)[4])pFsm->pTransitionMatrix;
	
	//pStateMatrix[0][0] = pFsm->pTransitionMatrix;
	
	//determine the State-Matrix-Element in dependany of current state and triggered event
	pFsm->presentState = pStateMatrix[pFsm->presentState][pFsm->ev].nextState;
	

	//do the transition to the next state (set requestet next state to current state)...
	
	//... and fire the proper action
//	(*stateEvaluation.actionToDo)();
	
}
