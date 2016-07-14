#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <Windows.h>
#include "FsmTest.h"
#include "IoDef.h"

void FsmRunner(void *pMyID);

inputIo_t in = { 0,0,0,5 };
outputIo_t out = { 0,0,0,0 };
BOOL run;

int main()
{
	char inp = 0;

	/* Start thread simulating a cyclic task running state machine*/
	_beginthread(FsmRunner, 0, NULL);

	/* Read keyborad input to simulate input, q for quit*/
	while (inp != 'q')
	{
		inp = _getch();

		switch (inp)
		{
		case '0':	/* Start and stop FSM running thread*/
			if (run)
			{
				run = FALSE;
			}
			else
			{
				_beginthread(FsmRunner, 0, NULL);
			}
			break;
		case '1':	/* Simulate start request*/
			in.startReq = in.startReq ? 0: 1;
			break;
		case '2':	/* Simulate stop request*/
			in.stopReq = in.stopReq ? 0 : 1;
			break;
		case '3':	/* Simulate running feedback*/
			in.running = in.running ? 0 : 1;
			break;
		case '4':
			in.timeout = 10;
			break;
		default:
			break;
		}
		printf("Input: %d %d %d\n", in.startReq, in.stopReq, in.running);
	}

	run = FALSE;	/* Make sure FSM running thread is stopped*/
	return 0;
}

void FsmRunner(void *pMyID)
{
	fsmData_t fsm = { 0 };

	InitFsmTest(&fsm, &in, &out);
	run = TRUE;

	while (run)
	{
		RunFsmTest(&fsm, &in);

		printf("Output: %d %d %d %d\n", *fsm.pState[eStopped].pOutput, *fsm.pState[eStarting].pOutput, *fsm.pState[eRunning].pOutput, *fsm.pState[eStopping].pOutput);

		Sleep(1000);
	}
	_endthread();
}

/*
void printfxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}*/
