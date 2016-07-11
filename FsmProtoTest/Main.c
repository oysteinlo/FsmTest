#include <stdio.h>
#include "FsmTest.h"

int main()
{
	fsmData_t fsm = { 0 };
	event ev[] = { eEvStartReq, eEvStarted, eEvStopReq, eEvStopped };
	int i;
	InitFsmTest(&fsm);
	
	for (i = 0; i < sizeof(ev)/ NUMOFEVENTS; i++)
	{
		fsm.ev = ev[i];
		RunFsmTest(&fsm);
	}

	return 0;
}