#pragma once
typedef state;
typedef void(*action)();
typedef event;
typedef int(*guard)(int *pA);

typedef struct stateElementType
{
	int *pOutput;
	char name[32];
	int timer;
	int timeout;
}stateElement_t;

typedef struct transitionElementType
{
	guard Guard;
	int *pTrigger;
	state nextState;       // Enumerator for the next state
	action actionToDo;     // function-pointer to the action that shall be released in current state
	int enter;
	int exit;
}  transElement_t;               // structure for the elements in the state-event matrix

typedef struct fsmDataType
{
	stateElement_t *pState;
	transElement_t *pTransitionMatrix;
	state presentState;
	int numStates;
	int numEvents;
	int enter;
	int exit;
	event ev;
} fsmData_t;

void SetTrigger(fsmData_t *pFsm, state st, event ev, int *pVal);
void SetStateTimer(stateElement_t *pState);
int DigNorm(int *pInp);
int DigInv(int *pInp);
