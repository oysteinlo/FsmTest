#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <Windows.h>
#include "FsmTest.h"
#include "IoDef.h"

void FsmRunner(void *pMyID);

inputIo_t in = { 0,0,0,0 };
outputIo_t out = { 0,0,0,0 };

int main()
{
	int ThreadId = 0;
	char inp = 0;
	int trigger = 0;

	_beginthread(FsmRunner, 0, &ThreadId);

	while (inp != 'q')
	{
		inp = _getch();

		switch (inp)
		{
		case '1':
			in.startReq = in.startReq ? 0: 1;
			break;
		case '2':
			in.stopReq = in.stopReq ? 0 : 1;
			break;
		case '3':
			in.running = in.running ? 0 : 1;
			break;
		case '4':
			in.stopped = in.stopped ? 0 : 1;
			break;
		default:
			break;
		}
		printf("Input: %d %d %d %d\n", in.startReq, in.stopReq, in.running, in.stopped);
	}

	return 0;
}

void FsmRunner(void *pMyID)
{
	fsmData_t fsm = { 0 };

	InitFsmTest(&fsm, &in, &out);

	for (;;)
	{
		RunFsmTest(&fsm);

		printf("Output: %d %d %d %d\n", *fsm.pState[eStopped].pOutput, *fsm.pState[eStarting].pOutput, *fsm.pState[eRunning].pOutput, *fsm.pState[eStopping].pOutput);

		Sleep(1000);
	}
	_endthread();
}



//TODO Inverted input
//TODO Timer function