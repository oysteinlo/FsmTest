#pragma once
typedef state;
typedef void(*action)();
typedef event;


typedef struct stateElementType
{
	state nextState;       // Enumerator for the next state
	char name[32];
	action actionToDo;     // function-pointer to the action that shall be released in current state
	
	int enter;
	int exit;
}  stateElement_t;               // structure for the elements in the state-event matrix

typedef struct fsmDataType
{
	stateElement_t *pTransitionMatrix;
	state presentState;
	int enter;
	int exit;
	event ev;
} fsmData_t;

