#include "cmd.h"

#include <assert.h>

// Win32 Equivalents for C Run-Time Functions
// https://support.microsoft.com/en-gb/kb/99456

HANDLE WINAPI GetProcessHeap(void) {
	return NULL;
}

BOOL WINAPI HeapFree(
  HANDLE hHeap,
  DWORD  dwFlags,
  LPVOID lpMem
) {
	assert( hHeap == NULL );
	assert( dwFlags == 0 );
	free(lpMem);
	return TRUE;
}

LPVOID WINAPI HeapReAlloc(
  HANDLE hHeap,
  DWORD  dwFlags,
  LPVOID lpMem,
  size_t dwBytes
) {
	assert( hHeap == NULL );
	assert( dwFlags == 0 );
	return realloc(lpMem, dwBytes);
}

LPVOID WINAPI HeapAlloc(
  HANDLE hHeap,
  DWORD  dwFlags,
  size_t dwBytes
) {
	assert( hHeap == NULL );
  void *data = malloc(dwBytes);
	if( dwFlags == HEAP_ZERO_MEMORY ) {
    memset(data, 0, dwBytes);
  }
  else {
    assert( dwFlags == 0 );
  }
	return data;
}

BOOL WINAPI ReadFile(
  FILE         *hFile,
  LPVOID       lpBuffer,
  DWORD        nNumberOfBytesToRead,
  LPDWORD      lpNumberOfBytesRead,
  LPVOID lpOverlapped
) {
	assert( hFile != NULL );
	assert( lpBuffer != NULL );
	DWORD bytes_read = fread(lpBuffer, 1, nNumberOfBytesToRead, hFile);
	if( lpNumberOfBytesRead ) {
		*lpNumberOfBytesRead = bytes_read;
	}
	return bytes_read == nNumberOfBytesToRead;
}

DWORD WINAPI GetFileSize(
  FILE  *hFile,
  LPDWORD lpFileSizeHigh
) {
  assert( lpFileSizeHigh == NULL );
  int prev=ftell(hFile);
  fseek(hFile, 0L, SEEK_END);
  int sz=ftell(hFile);
  fseek(hFile,prev,SEEK_SET); //go back to where we were
  return sz;
}

char* strtoupper(char* s) {
  assert(s != NULL);

  char* p = s;
  while (*p != '\0') {
    *p = toupper(*p);
    p++;
  }

  return s;
}

BOOL DeleteFile(LPCTSTR lpFileName) {
  if(remove(lpFileName) == 0) return TRUE;
  else return FALSE;
}

BOOL WINAPI CloseFile(
  FILE *hFile
) {
  return !fclose(hFile);
}

// https://github.com/timob/linapple/blob/956f6765bdd7508945ba642bd6da3b09148516c6/src/wwrapper.cpp
DWORD SetFilePointer(FILE *hFile,
       LONG lDistanceToMove,
       PLONG lpDistanceToMoveHigh,
       DWORD dwMoveMethod)  {
         /* ummm,fseek in Russian */
         fseek((FILE*)hFile, lDistanceToMove, dwMoveMethod);
         return ftell((FILE*)hFile);
}

// CreateFile
// https://github.com/bitcrystal/temp/blob/b6b32e4fa9abfa4007320e571b8beced1e353ed9/src/functions_hook/subhook/windows_defs2.c
