#include "_file.h"

#include <unistd.h>

int _pipe(  
	FILE **pfds,
	unsigned int psize,
	int textmode
)
{
	int fds[2];
	int ret = pipe(&fds[0]);
	if( ! ret ) {
		pfds[0] = fdopen(fds[0], "rw");
		pfds[1] = fdopen(fds[1], "rw");
	}
	return ret;
}


FILE *_dup2( FILE *oldfp, FILE *newfp )
{
	int oldfd, newfd;
	int res;

	if( oldfp==NULL || newfp==NULL ) return NULL;

	oldfd = fileno( oldfp );
	newfd = fileno( newfp );
	
	res = dup2( oldfd, newfd );

	if( res==-1) return NULL;
	else return newfp;
}


FILE* fdup(FILE* fp,char*mode)
{
	int fd;
	if(fp==NULL)return NULL;
	fd=dup(fileno(fp));
	return fdopen(fd,mode);
}


FILE *_dup( FILE *handle ) {
	return fdup(handle, "rwb");
}

// https://github.com/MathewWi/wiiapple/blob/edcab3f1d6e4c007ebfb4856071df4eee1838aaf/wiiapple/source/wwrapper.cpp
BOOL WriteFile(FILE* hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
		LPDWORD lpNumberOfBytesWritten, LPVOID lpOverlapped) {
	/* write something to file */
	DWORD byteswritten = fwrite(lpBuffer, 1, nNumberOfBytesToWrite, (FILE*)hFile);
	*lpNumberOfBytesWritten = byteswritten;
	return (nNumberOfBytesToWrite == byteswritten);
}


FILE* WINAPI GetStdHandle(
  _In_ DWORD nStdHandle
) {
	switch( nStdHandle )
	{
	case STD_INPUT_HANDLE:
		return STDIN;

	case STD_OUTPUT_HANDLE:
		return STDOUT;

	case STD_ERROR_HANDLE:
		return STDERR;

	default:
		abort();
	}
	return NULL;
}
