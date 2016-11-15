#ifndef _FILE_H__
#define _FILE_H__

#include "cmd.h"

FILE *_dup( FILE *handle );
  
int _pipe(  
	FILE **pfds,
	unsigned int psize,
	int textmode
);

BOOL WINAPI WriteFile(
	FILE*       hFile,
	LPCVOID      lpBuffer,
	DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
  	LPVOID lpOverlapped
);

FILE* WINAPI GetStdHandle(
  _In_ DWORD nStdHandle
);

#endif
