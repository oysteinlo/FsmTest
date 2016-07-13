#pragma once
typedef state;
typedef void(*action)();
typedef event;

typedef struct stateElementType
{
	int *pOutput;
	char name[32];
}stateElement_t;

typedef struct transitionElementType
{
	state nextState;       // Enumerator for the next state
	int *pTrigger;
	char name[32];
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


