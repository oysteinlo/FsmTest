#pragma once
typedef struct inputIoType
{
	int startReq;
	int stopReq;
	int running;
}inputIo_t;

typedef struct outputType
{
	int startReq;
	int stopReq;
	int run;
	int stopped;
}outputIo_t;
