#include "cmd.h"

#include <unistd.h>
#include <assert.h>
#include <libgen.h>
#include <sys/statvfs.h>

// Portable implementations of Windows Kernel32 functions
// https://github.com/sduirc/slippage-free/blob/c7ea1f3d69166e7ee61bd7668b58bee5dd8a8d08/Slippage/libc/BFC/filex.h
// https://github.com/sincoder/libx/blob/c09f390e38c0f3b1b91566654ec3c6cf8e113f48/kernel32.c
// https://github.com/paulopina21/plxJukebox-11/blob/193996ac99b99badab3a1d422806942afca2ad01/xbmc/linux/XFileUtils.cpp
// https://github.com/owen200008/ccbasic/blob/398474ac9d31abac09fc0d8ff2dc2bb714efdeef/src/file/file_linux.cpp


static DWORD ChangeFileAttributes(struct stat st)
{
	DWORD dwAttr = 0;
	if(st.st_mode & S_IFDIR)
	{
		dwAttr |= FILE_ATTRIBUTE_DIRECTORY;
	}
	if(st.st_mode & S_IFCHR)
	{
		dwAttr |= FILE_ATTRIBUTE_DEVICE;
	}
	if(st.st_mode & S_IFREG)
	{
		dwAttr |= FILE_ATTRIBUTE_NORMAL;
	}
	return dwAttr;
}


DWORD GetFileAttributes(LPCTSTR lpFileName)
{
	struct stat st;
	if(stat(lpFileName, &st) != 0)
	{
		return INVALID_FILE_ATTRIBUTES;
	}
	return ChangeFileAttributes(st);
}

BOOL SetFileAttributes(LPCTSTR lpFileName,DWORD dwFileAttributes)
{
	struct stat st;
	if(stat(lpFileName, &st) != 0)
	{
		return FALSE;
	}
	DWORD dwThisAttr = 0;
	if(access(lpFileName, W_OK) != 0)
	{
		dwThisAttr |= FILE_ATTRIBUTE_READONLY;
	}

	dwFileAttributes &= FILE_ATTRIBUTE_READONLY;
	if(dwFileAttributes == dwThisAttr)
	{
		return TRUE;
	}
	if(dwFileAttributes & FILE_ATTRIBUTE_READONLY)
	{
		st.st_mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);
	}
	else
	{
		st.st_mode |= (S_IWUSR | S_IWGRP | S_IWOTH);
	}
	return chmod(lpFileName, st.st_mode) == 0;
}

BOOL WINAPI MoveFile(
  _In_ LPCTSTR lpExistingFileName,
  _In_ LPCTSTR lpNewFileName
) {
	return ! rename(lpExistingFileName, lpNewFileName);
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

BOOL DeleteFile(LPCTSTR lpFileName) {
  return 0 == unlinkat(AT_FDCWD, lpFileName, 0);
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

BOOL WINAPI SetCurrentDirectory(
  _In_ LPCTSTR lpPathName
) {
	return ! chdir(lpPathName);
}

BOOL WINAPI GetBinaryType(
  _In_  LPCTSTR lpApplicationName,
  _Out_ LPDWORD lpBinaryType
) {
	struct stat sb;
	if( ! stat(lpApplicationName, &sb) ) {
		return sb.st_mode & S_IXUSR;
	}
	return FALSE;
}

DWORD WINAPI GetFullPathName(
  _In_  LPCTSTR lpFileName,
  _In_  DWORD   nBufferLength,
  _Out_ LPTSTR  lpBuffer,
  _Out_ LPTSTR  *lpFilePart
) {
	assert( lpFileName != NULL );
	assert( nBufferLength > 0 );
	assert( lpBuffer != NULL );

	char *data = realpath(lpFileName, NULL);
	if( data ) {
		strncpy(lpBuffer, data, nBufferLength);
		free(data);
		if( lpFilePart ) {
			*lpFilePart = basename(lpBuffer);
		}
		return strlen(lpBuffer);
	}
	// TODO: SetLastError
	return 0;
}

BOOL WINAPI WriteConsole(
  _In_             FILE*  hConsoleOutput,
  _In_       const VOID    *lpBuffer,
  _In_             DWORD   nNumberOfCharsToWrite,
  _Out_            LPDWORD lpNumberOfCharsWritten,
  _Reserved_       LPVOID  lpReserved
) {
	size_t nwritten = fwrite(lpBuffer, 1, nNumberOfCharsToWrite, hConsoleOutput);
	if( lpNumberOfCharsWritten ) {
		*lpNumberOfCharsWritten = nwritten;
	}
	return nwritten == nNumberOfCharsToWrite;
}


BOOL WINAPI CreateDirectory(
  _In_     LPCTSTR               lpPathName,
  _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes
) {
	return ! mkdir( lpPathName, 0644 );
}

DWORD WINAPI GetCurrentDirectory(
  _In_  DWORD  nBufferLength,
  _Out_ LPTSTR lpBuffer
) {
	return getcwd(lpBuffer, nBufferLength) != NULL;
}

UINT WINAPI GetWindowsDirectory(
  _Out_ LPTSTR lpBuffer,
  _In_  UINT   uSize
) {
	strncpy(lpBuffer, "/bin/", uSize);
	return strlen(lpBuffer);
}

BOOL WINAPI RemoveDirectory(
  _In_ LPCTSTR lpPathName
) {
	return ! unlink(lpPathName);
}

UINT WINAPI GetDriveType(
  _In_opt_ LPCTSTR lpRootPathName
) {
	return DRIVE_FIXED;
}

BOOL WINAPI SetFileTime(
  _In_           HANDLE   hFile,
  _In_opt_ const FILETIME *lpCreationTime,
  _In_opt_ const FILETIME *lpLastAccessTime,
  _In_opt_ const FILETIME *lpLastWriteTime
) {
	return FALSE;
}

BOOL WINAPI FlushFileBuffers(
  _In_ FILE* hFile
) {
	fflush(hFile);
	return TRUE;
}

BOOL WINAPI FlushConsoleInputBuffer(
  _In_ FILE* hConsoleInput
) {
	fpurge(hConsoleInput);
	return TRUE;
}

BOOL WINAPI GetDiskFreeSpace(
  _In_  LPCTSTR lpRootPathName,
  _Out_ LPDWORD lpSectorsPerCluster,
  _Out_ LPDWORD lpBytesPerSector,
  _Out_ LPDWORD lpNumberOfFreeClusters,
  _Out_ LPDWORD lpTotalNumberOfClusters
) {
	struct statvfs sb;
	if( statvfs(lpRootPathName, &sb) )
		return FALSE;

	if( lpSectorsPerCluster )
		*lpSectorsPerCluster = sb.f_frsize / sb.f_bsize;

	if( lpBytesPerSector )
		*lpBytesPerSector = sb.f_bsize;

	if( lpNumberOfFreeClusters )
		*lpNumberOfFreeClusters = sb.f_bfree / (sb.f_frsize / sb.f_bsize);

	if( lpTotalNumberOfClusters )
		*lpTotalNumberOfClusters = sb.f_blocks;

	return TRUE;
}

BOOL WINAPI CopyFile(
  _In_ LPCTSTR src,
  _In_ LPCTSTR dest,
  _In_ BOOL    bFailIfExists
) {
	if( bFailIfExists ) {
		struct stat sb;
		if( ! stat(dest, &sb) )
			return FALSE;
	}

  const unsigned int bufferSize = 16384;
  char buffer[bufferSize];
  FILE *hSrc = fopen(src, "rb");
  if (!hSrc) return FALSE;
  FILE *hDest = fopen(dest, "wb");
  if (!hDest)
  {
    fclose(hSrc);
    return FALSE;
  }
  BOOL ret = TRUE;
  while (ret)
  {
    int sizeRead = fread(buffer, 1, bufferSize, hSrc);
    if (sizeRead > 0)
    {
      int sizeWritten = fwrite(buffer, 1, sizeRead, hDest);
      if (sizeWritten != sizeRead)
      {
        ret = FALSE;
      }
    }
    else if (sizeRead < 0)
    {
      ret = FALSE;
    }
    else
      break;  // we're done
  }
  fclose(hSrc);
  fclose(hDest);
  return ret;
}


FILE*	CreateFile(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, 
				   DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
{
	TCHAR szOpenFlag[8];
	memset(szOpenFlag, 0, sizeof(szOpenFlag));
	switch(dwCreationDisposition)
	{
		case CREATE_NEW:
		{
			if (access(lpFileName, F_OK) == 0)	//文件存在，失败
			{
				SetLastError(EEXIST);
				return INVALID_HANDLE_VALUE;
			}
		}
		case CREATE_ALWAYS:
		{
			szOpenFlag[0] = 'w';
			break;
		}
		case OPEN_ALWAYS:
		{
			if (access(lpFileName, F_OK) == 0)	//文件存在，打开
			{
				szOpenFlag[0] = 'r';
			}
			else	//创建
			{
				szOpenFlag[0] = 'w';
			}
			break;
		}
		case TRUNCATE_EXISTING:
		{
			if (access(lpFileName, F_OK) != 0)	//文件不存在，失败
			{
				SetLastError(ENOENT);
				return INVALID_HANDLE_VALUE;
			}
			szOpenFlag[0] = 'w';
			break;
		}
		default:
		case OPEN_EXISTING:
		{
			szOpenFlag[0] = 'r';
			break;
		}
	}
	szOpenFlag[1] = 'b';
	if(dwDesiredAccess & GENERIC_WRITE)
	{
		szOpenFlag[2] = '+';
	}
	FILE* fp = fopen(lpFileName, szOpenFlag);
	if(fp == NULL)
	{
		return INVALID_HANDLE_VALUE;
	}
	return fp;
}

BOOL WINAPI GetVolumeInformation(
  _In_opt_  LPCTSTR lpRootPathName,
  _Out_opt_ LPTSTR  lpVolumeNameBuffer,
  _In_      DWORD   nVolumeNameSize,
  _Out_opt_ LPDWORD lpVolumeSerialNumber,
  _Out_opt_ LPDWORD lpMaximumComponentLength,
  _Out_opt_ LPDWORD lpFileSystemFlags,
  _Out_opt_ LPTSTR  lpFileSystemNameBuffer,
  _In_      DWORD   nFileSystemNameSize
) {
	if( lpVolumeNameBuffer ) {
		strncpy(lpVolumeNameBuffer, "ROOT", nVolumeNameSize);
	}
	if( lpVolumeSerialNumber )
		*lpVolumeSerialNumber = 0x12345678;
	if( lpMaximumComponentLength )
		*lpMaximumComponentLength = 0xFF;
	if( lpFileSystemFlags )
		*lpFileSystemFlags = 0x00000002 | 0x00000001 | 0x00000040;
	if( lpFileSystemNameBuffer )
		strncpy(lpFileSystemNameBuffer, "FAT", nFileSystemNameSize);
	return TRUE;
}

DWORD WINAPI SearchPath(
  _In_opt_  LPCTSTR lpPath,
  _In_      LPCTSTR lpFileName,
  _In_opt_  LPCTSTR lpExtension,
  _In_      DWORD   nBufferLength,
  _Out_     LPTSTR  lpBuffer,
  _Out_opt_ LPTSTR  *lpFilePart
) {
	abort();
	return 0;
}

BOOL WINAPI SetConsoleCtrlHandler(
  _In_opt_ PHANDLER_ROUTINE HandlerRoutine,
  _In_     BOOL             Add
) {
	//abort();
	return FALSE;
}

typedef struct _FIND_FILE_HANDLE
{
    int fp; // 文件夹的 fd
    unsigned int idx; //文件的编号
} FIND_FILE_HANDLE;


HANDLE FindFirstFile(
    _In_   LPCTSTR lpFileName,
    _Out_  LPWIN32_FIND_DATA lpFindFileData
)
{
    int DirFp = -1;
    if (!lpFileName)
        return INVALID_HANDLE_VALUE;
    DirFp = openat(AT_FDCWD, lpFileName, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (DirFp)
    {
        if (lpFindFileData)
        {
            FIND_FILE_HANDLE *pHandle = (FIND_FILE_HANDLE *)malloc(sizeof(FIND_FILE_HANDLE));
            if (pHandle)
            {
                memset(lpFindFileData, 0, sizeof(WIN32_FIND_DATA));
                strcpy(lpFindFileData->cFileName, "."); // fake first file name
                lpFindFileData->dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

                pHandle->fp = DirFp;
                pHandle->idx = 0;
                return (HANDLE)pHandle;
            }
        }
        close(DirFp);
    }
    return INVALID_HANDLE_VALUE;
}


struct linux_dirent
{
    long           d_ino;
    off_t          d_off;
    unsigned short d_reclen;
    char           d_name[];
};


// https://github.com/sincoder/libx/blob/master/kernel32.c
BOOL FindNextFile(
    _In_   HANDLE hFindFile,
    _Out_  LPWIN32_FIND_DATA lpFindFileData
)
{
	/*
    FIND_FILE_HANDLE *pHandle = (FIND_FILE_HANDLE *)hFindFile;
    if (pHandle && lpFindFileData)
    {
        struct linux_dirent *d;
        char buff[1024];
        //int i = 0;
        int ok = 0;
        while ( 1 != ok )
        {
            int bpos, nread;
            char d_type;
            int inputLen = 1;
            // get one file
            while (1)
            {
                nread = syscall(SYS_getdents, pHandle->fp, buff, inputLen);
                if (nread == -1 )
                {
                    if (errno == EINVAL)
                    {
                        inputLen ++;
                        continue;
                    }
                }
                break;
            }

            if (nread == -1)
            {
                //dbg_msg("getdent error,error no : %d ", errno);
                break;
            }
            if (nread == 0)
                break;

            for (bpos = 0; bpos < nread;)
            {
                d = (struct linux_dirent *) (buff + bpos);
                if (strcmp(d->d_name, ".") == 0 )
                {
                    pHandle->idx ++;// skip .
                }
                else
                {
                    d_type = *(buff + bpos + d->d_reclen - 1);
                    lpFindFileData->dwFileAttributes =
                        (d_type == DT_DIR ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL);
                    strncpy(lpFindFileData->cFileName,
                                 d->d_name,
                                 sizeof(lpFindFileData->cFileName));
                    ok = 1;
                    break;
                }
                bpos += d->d_reclen;
            }
        }

        if (ok)
        {
            pHandle->idx ++;
            return TRUE;
        }
    }
    return FALSE;
    */
    abort();
    return FALSE;
}

BOOL FindClose(
    _Inout_  HANDLE hFindFile
)
{
    if (hFindFile)
    {
        FIND_FILE_HANDLE *p = (FIND_FILE_HANDLE *)hFindFile;
        close(p->fp);
        free(p);
        return TRUE;
    }
    return FALSE;
}