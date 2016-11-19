#include "cmd.h"

#include <unistd.h>
#include <assert.h>
#include <libgen.h>
#include <sys/statvfs.h>
#include <dirent.h>

// Portable implementations of Windows Kernel32 functions
// https://github.com/sduirc/slippage-free/blob/c7ea1f3d69166e7ee61bd7668b58bee5dd8a8d08/Slippage/libc/BFC/filex.h
// https://github.com/sincoder/libx/blob/c09f390e38c0f3b1b91566654ec3c6cf8e113f48/kernel32.c
// https://github.com/paulopina21/plxJukebox-11/blob/193996ac99b99badab3a1d422806942afca2ad01/xbmc/linux/XFileUtils.cpp
// https://github.com/owen200008/ccbasic/blob/398474ac9d31abac09fc0d8ff2dc2bb714efdeef/src/file/file_linux.cpp

static void
str_replace( char *str, char find_char, char replace_char ) {
  while( *str ) {
    if( *str == '\\' ) {
      *str = '/';
    }
    str++;
  }
}

/** Convert C:\Dos\Path to /Dos/Path */
static char *
DOSPath2UNIXPath( const char* dos_path ) {
  assert( dos_path != NULL );

  char *unix_path = malloc(strlen(dos_path));

  if( dos_path[1] == ':' ) {
    if( toupper(dos_path[0]) != 'C' ) {
      SetLastError(ERROR_INVALID_DRIVE);
      abort();
      return NULL;
    }
    strcpy(unix_path, &dos_path[2]);
  }
  else {
    strcpy(unix_path, dos_path);
  }

  str_replace(unix_path, '\\', '/');
  return unix_path;
}

/** Convert /Unix/Path to C:\Unix\Path */
static char *
UNIXPath2DOSPath( const char *unix_path ) {
  assert( unix_path != NULL );
  assert( unix_path[0] == '/' );
  char *dos_path = malloc(strlen(unix_path) + 2);
  dos_path[0] = 'C';
  dos_path[1] = ':';
  strcpy(&dos_path[2], unix_path);
  str_replace(dos_path, '/', '\\');
  return dos_path;
}

static DWORD
ChangeFileAttributes(struct stat st)
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


DWORD
GetFileAttributes(LPCTSTR lpFileName)
{
	struct stat st;
  char *unix_path = DOSPath2UNIXPath(lpFileName);
  int ret = stat(lpFileName, &st);
  free(unix_path);
	if(ret != 0)
	{
		return INVALID_FILE_ATTRIBUTES;
	}
	return ChangeFileAttributes(st);
}

BOOL
SetFileAttributes(LPCTSTR lpFileName, DWORD dwFileAttributes)
{
	struct stat st;
  BOOL ret = FALSE;
  char *unix_path = DOSPath2UNIXPath(lpFileName);

	if(stat(unix_path, &st) == 0)
  {
    DWORD dwThisAttr = 0;
    if(access(unix_path, W_OK) != 0)
    {
      dwThisAttr |= FILE_ATTRIBUTE_READONLY;
    }

    dwFileAttributes &= FILE_ATTRIBUTE_READONLY;
    if(dwFileAttributes != dwThisAttr)
    {
      if(dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
        st.st_mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);
      }
      else {
        st.st_mode |= (S_IWUSR | S_IWGRP | S_IWOTH);
      }
      ret = (chmod(unix_path, st.st_mode) == 0);
      if( ! ret ) {
        // TODO: replace with errno to ERROR converter
        SetLastError(ERROR_INVALID_FUNCTION);
      }
    }
    else {
      ret = TRUE;
    }
  }
  else {
    SetLastError(ERROR_FILE_NOT_FOUND);
	}

  free(unix_path);
  return ret;
}

BOOL WINAPI MoveFile(
  _In_ LPCTSTR lpExistingFileName,
  _In_ LPCTSTR lpNewFileName
) {
  char *unix_existing = DOSPath2UNIXPath(lpExistingFileName);
  char *unix_new = DOSPath2UNIXPath(lpNewFileName);
	BOOL ret = ! rename(lpExistingFileName, lpNewFileName);
  // TODO: SetLastError errno to ERROR converter
  free(unix_existing);
  free(unix_new);
  return ret;
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
  char *unix_path = DOSPath2UNIXPath(lpFileName);
  BOOL ret = 0 == unlink(unix_path);
  free(unix_path);
  return ret;
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
  char *unix_path = DOSPath2UNIXPath(lpPathName);
	BOOL ret = ! chdir(lpPathName);
  free(unix_path);
  return ret;
}

BOOL WINAPI GetBinaryType(
  _In_  LPCTSTR lpApplicationName,
  _Out_ LPDWORD lpBinaryType
) {
	struct stat sb;
  BOOL ret = FALSE;
  char *unix_path = DOSPath2UNIXPath(lpApplicationName);
	if( ! stat(lpApplicationName, &sb) ) {
		ret = sb.st_mode & S_IXUSR;
	}
  free(unix_path);
	return ret;
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
  DWORD ret = 0;
  char *unix_path = DOSPath2UNIXPath(lpFileName);
	char *data = realpath(lpFileName, NULL);
	if( data ) {
		strncpy(lpBuffer, data, nBufferLength);
		free(data);
		if( lpFilePart ) {
			*lpFilePart = basename(lpBuffer);
		}
		ret = strlen(lpBuffer);
	}
  else {
	 // TODO: SetLastError
  }
  free(unix_path);
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
  DWORD ret = 0;
  char *wd = getwd(NULL);
  char *dos_path = UNIXPath2DOSPath(wd);
  strncpy(lpBuffer, dos_path, nBufferLength);	
  ret = strlen(lpBuffer);
  free(wd);
  free(dos_path);
  return ret;
}

UINT WINAPI GetWindowsDirectory(
  _Out_ LPTSTR lpBuffer,
  _In_  UINT   uSize
) {
	strncpy(lpBuffer, "C:\\BIN\\", uSize);
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

BOOL WINAPI SetConsoleCtrlHandler(
  _In_opt_ PHANDLER_ROUTINE HandlerRoutine,
  _In_     BOOL             Add
) {
	//abort();
	return FALSE;
}

typedef struct _FIND_FILE_HANDLE
{
    DIR *fp;
    struct dirent entry;
} FIND_FILE_HANDLE;


HANDLE FindFirstFile(
    _In_   LPCTSTR lpFileName,
    _Out_  LPWIN32_FIND_DATA lpFindFileData
)
{
    DIR *DirFp = NULL;
    if (!lpFileName) {
        SetLastError(ERROR_INVALID_PARAMETER);
        return INVALID_HANDLE_VALUE;
    }
    DirFp = opendir(lpFileName);
    if (DirFp)
    {
        if (lpFindFileData)
        {
            FIND_FILE_HANDLE *pHandle = (FIND_FILE_HANDLE *)malloc(sizeof(FIND_FILE_HANDLE));
            if (pHandle)
            {
                memset(lpFindFileData, 0, sizeof(WIN32_FIND_DATA));
                pHandle->fp = DirFp;
                
                strcpy(lpFindFileData->cFileName, "."); // fake first file name
                lpFindFileData->dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

                return (HANDLE)pHandle;
            }
        }
        closedir(DirFp);
    }
    SetLastError(ERROR_FILE_NOT_FOUND);
    return INVALID_HANDLE_VALUE;
}


BOOL FindNextFile(
    _In_   HANDLE hFindFile,
    _Out_  LPWIN32_FIND_DATA lpFindFileData
)
{
	FIND_FILE_HANDLE *pHandle = (FIND_FILE_HANDLE *)hFindFile;
	if (pHandle && lpFindFileData)
    {
    	while( TRUE ) {    		
			struct dirent *result;
			if( -1 == readdir_r(pHandle->fp, &pHandle->entry, &result) ) {
				return FALSE;
			}

			if (strcmp(result->d_name, ".") != 0 ) {
	            lpFindFileData->dwFileAttributes =
	                (result->d_type == DT_DIR ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL);
	            strncpy(lpFindFileData->cFileName,
	                         result->d_name,
	                         sizeof(lpFindFileData->cFileName));
	            return TRUE;
	        }
    	}
    }
    return FALSE;
}

BOOL FindClose(
    _Inout_  HANDLE hFindFile
)
{
    if (hFindFile)
    {
        FIND_FILE_HANDLE *p = (FIND_FILE_HANDLE *)hFindFile;
        closedir(p->fp);
        free(p);
        return TRUE;
    }
    return FALSE;
}

// https://github.com/erick2red/coreclr/blob/d872d88defabcce0f9a1a92d2ddd4b1ded105d46/src/pal/src/file/path.cpp
DWORD
SearchPath(
    IN LPCSTR lpPath,
    IN LPCSTR lpFileName,
    IN LPCSTR lpExtension,
    IN DWORD nBufferLength,
    OUT LPSTR lpBuffer,
    OUT LPSTR *lpFilePart
    )
{
    DWORD nRet = 0;
    CHAR * FullPath;
    size_t FullPathLength = 0;
    //PathCharString FullPathPS;
    //PathCharString CanonicalFullPathPS;
    CHAR * CanonicalFullPath;
    LPCSTR pPathStart;
    LPCSTR pPathEnd;
    size_t PathLength;
    size_t FileNameLength;
    DWORD length;
    DWORD dw;

    /*
    ENTRY("SearchPathA(lpPath=%p (%s), lpFileName=%p (%s), lpExtension=%p, "
          "nBufferLength=%u, lpBuffer=%p, lpFilePart=%p)\n",
      lpPath,
      lpPath, lpFileName, lpFileName, lpExtension, nBufferLength, lpBuffer, 
          lpFilePart);
     */

    /* validate parameters */
    
    if(NULL == lpPath)
    {
        //assert("lpPath may not be NULL\n");
        SetLastError(ERROR_INVALID_PARAMETER);
        goto done;
    }
    if(NULL == lpFileName)
    {
        //assert("lpFileName may not be NULL\n");
        SetLastError(ERROR_INVALID_PARAMETER);
        goto done;
    }
    if(NULL != lpExtension)
    {
        //assert("lpExtension must be NULL, is %p instead\n", lpExtension);
        SetLastError(ERROR_INVALID_PARAMETER);
        goto done;
    }

    FileNameLength = strlen(lpFileName);

    /* special case : if file name contains absolute path, don't search the 
       provided path */
    if('\\' == lpFileName[0] || '/' == lpFileName[0])
    {
        /* Canonicalize the path to deal with back-to-back '/', etc. */
        length = FileNameLength;
        CanonicalFullPath = malloc(length); //CanonicalFullPathPS.OpenStringBuffer(length);
        if (NULL == CanonicalFullPath)
        {
            SetLastError(ERROR_NOT_ENOUGH_MEMORY);
            goto done;
        }
        dw = GetFullPathName(lpFileName, length+1, CanonicalFullPath, NULL);
        //CanonicalFullPathPS.CloseBuffer(dw);
        
        if (length+1 < dw)
        {
            CanonicalFullPath = realloc(CanonicalFullPath, dw-1); // CanonicalFullPathPS.OpenStringBuffer(dw-1);
            if (NULL == CanonicalFullPath)
            {
                SetLastError(ERROR_NOT_ENOUGH_MEMORY);
                goto done;
            }
            dw = GetFullPathName(lpFileName, dw,
                                  CanonicalFullPath, NULL);
            //CanonicalFullPathPS.CloseBuffer(dw);
        }

        if (dw == 0) 
        {
            /*WARN("couldn't canonicalize path <%s>, error is %#x. failing.\n",
                 lpFileName, GetLastError());*/
            SetLastError(ERROR_INVALID_PARAMETER);
            goto done;
        }

        /* see if the file exists */
        if(0 == access(CanonicalFullPath, F_OK))
        {
            /* found it */
            nRet = dw;
        }
    }
    else
    {
        LPCSTR pNextPath;
        pNextPath = lpPath;
    
        while (*pNextPath) 
        {
            pPathStart = pNextPath;
            
            /* get a pointer to the end of the first path in pPathStart */
            pPathEnd = strchr(pPathStart, ':');
            if (!pPathEnd)
            {
                pPathEnd = pPathStart + strlen(pPathStart);
                /* we want to break out of the loop after this pass, so let
                   *pNextPath be '\0' */
                pNextPath = pPathEnd;
            }
            else
            {
                /* point to the next component in the path string */
                pNextPath = pPathEnd+1;
            }
    
            PathLength = pPathEnd-pPathStart;
    
            if(0 == PathLength)
            {
                /* empty component : there were 2 consecutive ':' */
                continue;
            }
    
            /* Construct a pathname by concatenating one path from lpPath, '/' 
               and lpFileName */
            FullPathLength = PathLength + FileNameLength;
            FullPath = malloc(FullPathLength+1); // FullPathPS.OpenStringBuffer(FullPathLength+1);
            if (NULL == FullPath)
            {
                SetLastError(ERROR_NOT_ENOUGH_MEMORY);
                goto done;
            }
            memcpy(FullPath, pPathStart, PathLength);
            FullPath[PathLength] = '/';
            if (NULL == strncpy(&FullPath[PathLength+1], lpFileName, FullPathLength+1-PathLength) )
            {
                //ERROR("strcpy failed!\n");
                SetLastError( ERROR_FILENAME_EXCED_RANGE );
                nRet = 0;
                goto done;
            }

            //FullPathPS.CloseBuffer(FullPathLength+1);            
            /* Canonicalize the path to deal with back-to-back '/', etc. */
            length = MAX_PATH; //MAX_LONGPATH; //Use it for first try
            CanonicalFullPath = malloc(length); //CanonicalFullPathPS.OpenStringBuffer(length);
            if (NULL == CanonicalFullPath)
            {
                SetLastError(ERROR_NOT_ENOUGH_MEMORY);
                goto done;
            }
            dw = GetFullPathName(FullPath, length+1,
                                  CanonicalFullPath, NULL);
            //CanonicalFullPathPS.CloseBuffer(dw);
            
            if (length+1 < dw)
            {
                CanonicalFullPath = realloc(CanonicalFullPath, dw-1); //CanonicalFullPathPS.OpenStringBuffer(dw-1);
                dw = GetFullPathName(FullPath, dw,
                                      CanonicalFullPath, NULL);
                //CanonicalFullPathPS.CloseBuffer(dw);
            }
            
            if (dw == 0) 
            {
                /* Call failed - possibly low memory.  Skip the path */
                /*WARN("couldn't canonicalize path <%s>, error is %#x. "
                     "skipping it\n", FullPath, GetLastError());*/
                continue;
            }
    
            /* see if the file exists */
            if(0 == access(CanonicalFullPath, F_OK))
            {
                /* found it */
                nRet = dw;
                break;
            }
        }
    }

    if (nRet == 0) 
    {
       /* file not found anywhere; say so. in Windows, this always seems to say
          FILE_NOT_FOUND, even if path doesn't exist */
       SetLastError(ERROR_FILE_NOT_FOUND);
    }
    else
    {
        if (nRet < nBufferLength) 
        {
            if(NULL == lpBuffer)
            {
                /* Windows merily crashes here, but let's not */
                /*ERROR("caller told us buffer size was %d, but buffer is NULL\n",
                      nBufferLength);*/
                SetLastError(ERROR_INVALID_PARAMETER);
                nRet = 0;
                goto done;
            }
            
            if (strncpy(lpBuffer, CanonicalFullPath, nBufferLength))
            {
                //ERROR("strcpy failed!\n");
                SetLastError( ERROR_FILENAME_EXCED_RANGE );
                nRet = 0;
                goto done;
            }

            if(NULL != lpFilePart)
            {
                *lpFilePart = strrchr(lpBuffer,'/');
                if(NULL == *lpFilePart)
                {
                    //assert("no '/' in full path!\n");
                    abort();
                }
                else
                {
                    /* point to character after last '/' */
                    (*lpFilePart)++;
                }
            }
        }
        else
        {
            /* if buffer is too small, report required length, including 
               terminating null */
            nRet++;
        }
    }
done:
    //LOGEXIT("SearchPathA returns DWORD %u\n", nRet);
    return nRet;
}
