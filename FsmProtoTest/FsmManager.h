

typedef state_t;
typedef void(*action)(void *pA);
typedef event_t;
typedef int(*guard)(void *pA);

/* Datastructure for state element*/
typedef struct stateElementType
{
	int *pOutput;			/* Pointer to generic output data, one for each state*/
	char name[32];			/* State name*/
	int *pTimeout;			/* Timeout limit for state (if timout trigger configured)*/
	int timer;				/* Timeout counter*/
}stateElement_t;

/* Datastructure for transition element*/
typedef struct transitionElementType
{
	guard funcGuard;		/* Function pointer to guard function. When TRUE transition is performed*/
	void *pTrigger;			/* Pointer to trigger data used on guard function*/
	state_t nextState;		/* Enumerator for the next state*/
	action actionToDo;		/* Function-pointer to the action run in the transition*/
}  transElement_t;               

/* Datastructure for state machine*/
typedef struct fsmDataType
{
	stateElement_t *pState;				/* Pointer to array of states*/
	transElement_t *pTransitionMatrix;	/* Pointer to array of transition elements*/
	state_t presentState;					/* Enumeration for present state*/
	int numStates;						/* Total number of states*/
	int numEvents;						/* Total number of events*/
	int enter;							/* TRUE the first scan in a new state, can be used to perform custom actions*/	
	int printFlag;						/* Flag for enabling debug printouts(Not in use at the momen...t)*/
} fsmData_t;


void StateEval(fsmData_t *pFsm);
void SetTrigger(fsmData_t *pFsm, state_t st, event_t ev, int *pVal);
void SetStateTimer(stateElement_t *pState);
int DigNorm(int *pInp);
int DigInv(int *pInp);
int Timer(stateElement_t *state);