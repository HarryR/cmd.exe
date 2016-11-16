#ifndef COMPAT_H_
#define COMPAT_H_

// Oracle says this code is fine to copy from MSDN because it's just APIs...

#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <wchar.h>
#include <stddef.h>

#define WIN95_CMD
#define PORTABLE_CMD

#define MAX_PATH PATH_MAX

#define CONST const

#define O_BINARY 0
#define _O_APPEND O_APPEND
#define _O_BINARY O_BINARY

#define INFINITE  0xFFFFFFFF
#define CONTROL_C_EXIT   ((DWORD)0xC000013A)
#define CTRL_C_EVENT 0
#define CTRL_BREAK_EVENT 1


// See: https://msdn.microsoft.com/en-gb/library/windows/desktop/aa383751(v=vs.85).aspx
typedef unsigned char BYTE;
typedef unsigned char *PBYTE;
typedef char TCHAR, *LPTCH;
typedef char CHAR;
typedef char CCHAR;
typedef wchar_t WCHAR;
typedef WCHAR *LPWSTR;
typedef unsigned char UCHAR;
typedef CHAR *PCHAR;
typedef CONST CHAR *LPCSTR;
typedef CONST CHAR *LPCTSTR;
typedef uint16_t WORD;
typedef int32_t LONG;
typedef LONG *PLONG;
typedef uint32_t ULONG, UINT;
typedef ULONG *PULONG;
typedef TCHAR* PTCHAR;
typedef void VOID;
typedef VOID* PVOID;
typedef CONST VOID* LPCVOID;
typedef unsigned short USHORT;
typedef bool BOOLEAN;
typedef bool BOOL;
typedef BOOL* PBOOL;
typedef BOOL* LPBOOL;
typedef uint32_t DWORD;
typedef DWORD *LPDWORD;
typedef int64_t LONGLONG;
typedef PVOID HANDLE, *PHANDLE, *LPHANDLE;
typedef HANDLE HINSTANCE, HMODULE;
typedef HANDLE HWND;
typedef HANDLE* PHANDLE;
typedef HANDLE HKEY;
typedef unsigned char BYTE, *LPBYTE;
typedef void *LPVOID;
typedef size_t SIZE_T;

typedef HANDLE HDESK, HWINSTA;
#define SW_SHOWNORMAL 1

typedef uint64_t ULONGLONG;
typedef ULONGLONG *PULONGLONG;

#define FALSE false
#define TRUE true

typedef char *LPSTR;
#ifdef UNICODE
 typedef LPWSTR LPTSTR;
#else
 typedef LPSTR LPTSTR;
#endif

typedef union _LARGE_INTEGER {
  struct {
    DWORD LowPart;
    LONG  HighPart;
  };
  struct {
    DWORD LowPart;
    LONG  HighPart;
  } u;
  LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;

typedef union _ULARGE_INTEGER {
  struct {
    DWORD LowPart;
    DWORD HighPart;
  };
  struct {
    DWORD LowPart;
    DWORD HighPart;
  } u;
  ULONGLONG QuadPart;
} ULARGE_INTEGER, *PULARGE_INTEGER;

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms724284(v=vs.85).aspx
typedef struct _FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

// https://msdn.microsoft.com/en-us/library/windows/desktop/aa365740(v=vs.85).aspx
typedef struct _WIN32_FIND_DATA {
  DWORD    dwFileAttributes;
  FILETIME ftCreationTime;
  FILETIME ftLastAccessTime;
  FILETIME ftLastWriteTime;
  DWORD    nFileSizeHigh;
  DWORD    nFileSizeLow;
  DWORD    dwReserved0;
  DWORD    dwReserved1;
  TCHAR    cFileName[MAX_PATH];
  TCHAR    cAlternateFileName[14];
} WIN32_FIND_DATA, *PWIN32_FIND_DATA, *LPWIN32_FIND_DATA;

typedef struct _SHELLEXECUTEINFO {
  DWORD     cbSize;
  ULONG     fMask;
  HWND      hwnd;
  LPCTSTR   lpVerb;
  LPCTSTR   lpFile;
  LPCTSTR   lpParameters;
  LPCTSTR   lpDirectory;
  int       nShow;
  HINSTANCE hInstApp;
  LPVOID    lpIDList;
  LPCTSTR   lpClass;
  HKEY      hkeyClass;
  DWORD     dwHotKey;
  union {
    HANDLE hIcon;
    HANDLE hMonitor;
  } DUMMYUNIONNAME;
  HANDLE    hProcess;
} SHELLEXECUTEINFO, *LPSHELLEXECUTEINFO;


// https://msdn.microsoft.com/en-us/library/windows/desktop/ms686331(v=vs.85).aspx
typedef struct _STARTUPINFO {
  DWORD  cb;
  LPTSTR lpReserved;
  LPTSTR lpDesktop;
  LPTSTR lpTitle;
  DWORD  dwX;
  DWORD  dwY;
  DWORD  dwXSize;
  DWORD  dwYSize;
  DWORD  dwXCountChars;
  DWORD  dwYCountChars;
  DWORD  dwFillAttribute;
  DWORD  dwFlags;
  WORD   wShowWindow;
  WORD   cbReserved2;
  LPBYTE lpReserved2;
  HANDLE hStdInput;
  HANDLE hStdOutput;
  HANDLE hStdError;
} STARTUPINFO, *LPSTARTUPINFO;

typedef struct _PROCESS_INFORMATION {
  HANDLE hProcess;
  HANDLE hThread;
  DWORD  dwProcessId;
  DWORD  dwThreadId;
} PROCESS_INFORMATION, *LPPROCESS_INFORMATION;

typedef struct _SECURITY_ATTRIBUTES {
  DWORD  nLength;
  LPVOID lpSecurityDescriptor;
  BOOL   bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;


// https://msdn.microsoft.com/en-us/library/windows/desktop/ms724950(v=vs.85).aspx
typedef struct _SYSTEMTIME {
  WORD wYear;
  WORD wMonth;
  WORD wDayOfWeek;
  WORD wDay;
  WORD wHour;
  WORD wMinute;
  WORD wSecond;
  WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms724251(v=vs.85).aspx
#define DUPLICATE_CLOSE_SOURCE 0x00000001

#define WINAPI
#define _CRTAPI1

// https://msdn.microsoft.com/en-us/library/windows/desktop/aa363854(v=vs.85).aspx
typedef DWORD (WINAPI *LPPROGRESS_ROUTINE)(
         LARGE_INTEGER TotalFileSize,
         LARGE_INTEGER TotalBytesTransferred,
         LARGE_INTEGER StreamSize,
         LARGE_INTEGER StreamBytesTransferred,
         DWORD         dwStreamNumber,
         DWORD         dwCallbackReason,
         HANDLE        hSourceFile,
         HANDLE        hDestinationFile,
    	 LPVOID        lpData
);

DWORD WINAPI GetLastError(void);
void WINAPI SetLastError(DWORD dwErrCode);

LPTSTR WINAPI GetCommandLine(void);
VOID WINAPI SetCommandLine(int argc, char **argv);
DWORD WINAPI GetVersion(void);

char *strtolower(char *buf);
char* strtoupper(char* s);

#define _tcslwr strtolower
#define lstrcmpi strcasecmp
#define _tcsstr strstr
#define _tcsrchr strrchr
#define _tcsicmp strcasecmp
#define _tcschr strchr
#define _tcslen strlen
#define _tcscpy strcpy
#define _tcsncpy strncpy
#define _tcscat strcat
#define _tcsncmp strncmp
#define _tcscmp strcmp
#define _tcstol strtol
#define _tcsnicmp strncasecmp
#define _tcsupr strtoupper
#define _istspace isspace
#define _istxdigit isxdigit
#define _istalpha isalpha
#define _istdigit isdigit
#define _totlower tolower
#define _totupper toupper
#define _sntprintf snprintf
#define _stprintf sprintf
#define _vsntprintf vsnprintf 
#define _vsnprintf vsnprintf 
#define TEXT(x) x
#define __TEXT(x) x

#define _getch getchar

#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))

#define UNREFERENCED_PARAMETER(p)          ((p)=(p))
#define DBG_UNREFERENCED_PARAMETER(p)      ((p)=(p))
#define DBG_UNREFERENCED_LOCAL_VARIABLE(p) ((p)=(p))

#define _In_
#define _In_opt_
#define _Inout_opt_
#define _Inout_
#define _Reserved_
#define _Out_
#define _Out_opt_
#define IN
#define OUT
#define OPTIONAL

// http://ftp.icpdas.com/pub/beta_version/VHM/wince600/at91sam9g45m10ek_armv4i/cesysgen/ddk/inc/ntintsafe.h
#ifndef UInt32x32To64
#define UInt32x32To64(a, b) ((uint64_t)((unsigned long)(a)) * (uint64_t)((unsigned long)(b)))
#endif // !UInt32x32To64

void _ultoa(unsigned long value, char* string, unsigned char radix);
void _ltoa(long value, char* string, unsigned char radix);

BOOL WINAPI GetConsoleMode(
  _In_  FILE*  hConsoleHandle,
  _Out_ LPDWORD lpMode
);

DWORD WINAPI GetConsoleTitle(
  _Out_ LPTSTR lpConsoleTitle,
  _In_  DWORD  nSize
);

BOOL WINAPI SetConsoleTitle(
  _In_ LPCTSTR lpConsoleTitle
);

void WINAPI DebugBreak(void);


#define INVALID_HANDLE_VALUE NULL
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms681382(v=vs.85).aspx
#define NO_ERROR 0
#define ERROR_SUCCESS 0
#define ERROR_INVALID_FUNCTION 1
#define ERROR_FILE_NOT_FOUND 2
#define ERROR_PATH_NOT_FOUND 3
#define ERROR_TOO_MANY_OPEN_FILES 4
#define ERROR_ACCESS_DENIED 5
#define ERROR_INVALID_HANDLE 6
#define ERROR_ARENA_TRASHED 7
#define ERROR_NOT_ENOUGH_MEMORY 8
#define ERROR_BAD_ENVIRONMENT 10
#define ERROR_INVALID_ACCESS 12
#define ERROR_INVALID_DRIVE 15
#define ERROR_NO_MORE_FILES 18
#define ERROR_NOT_READY 21
#define ERROR_NOT_DOS_DISK 26
#define ERROR_SECTOR_NOT_FOUND 27
#define ERROR_WRITE_FAULT 29
#define ERROR_SHARING_VIOLATION 32
#define ERROR_LOCK_VIOLATION 33
#define ERROR_HANDLE 38
#define ERROR_FILE_EXISTS 80
#define ERROR_CANNOT_MAKE 82
#define ERROR_ALREADY_ASSIGNED 85
#define ERROR_INVALID_PARAMETER 87
#define ERROR_NO_PROC_SLOTS 89
#define ERROR_DRIVE_LOCKED 108
#define ERROR_OPEN_FAILED 110
#define ERROR_BUFFER_OVERFLOW 111
#define ERROR_DISK_FULL 112
#define ERROR_INVALID_NAME 123
#define ERROR_CHILD_NOT_COMPLETE 129
#define ERROR_DIR_NOT_ROOT 144
#define ERROR_DIR_NOT_EMPTY 145
#define ERROR_INVALID_ORDINAL 182
#define ERROR_ALREADY_EXISTS 183
#define ERROR_INVALID_STARTING_CODESEG 188
#define ERROR_INVALID_STACKSEG 189
#define ERROR_INVALID_MODULETYPE 190
#define ERROR_INVALID_EXE_SIGNATURE 191
#define ERROR_EXE_MARKED_INVALID 192
#define ERROR_BAD_EXE_FORMAT 193
#define ERROR_INVALID_MINALLOCSIZE 195
#define ERROR_INFLOOP_IN_RELOC_CHAIN 202
#define ERROR_ENVVAR_NOT_FOUND 203
#define ERROR_FILENAME_EXCED_RANGE 206
#define ERROR_EXE_MACHINE_TYPE_MISMATCH 216
#define ERROR_MORE_DATA 234
#define ERROR_NO_MORE_ITEMS 259
#define ERROR_DIRECTORY 267
#define ERROR_MR_MID_NOT_FOUND 317
#define ERROR_OPERATION_ABORTED 995
#define ERROR_NO_MEDIA_IN_DRIVE 1112
#define ERROR_BAD_DEVICE 1200
#define ERROR_REQUEST_ABORTED 1235
#define ERROR_PRIVILEGE_NOT_HELD 1314
#define ERROR_NOT_ENOUGH_QUOTA 1816
#define ERROR_NOT_CONNECTED 2250

#define FILE_ATTRIBUTE_READONLY 1
#define FILE_ATTRIBUTE_HIDDEN 2
#define FILE_ATTRIBUTE_SYSTEM 4
#define FILE_ATTRIBUTE_DIRECTORY 0x10
#define FILE_ATTRIBUTE_DEVICE 0x40
#define FILE_ATTRIBUTE_ARCHIVE 32
#define FILE_ATTRIBUTE_NORMAL 128
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED 8192
#define FILE_ATTRIBUTE_OFFLINE 4096
#define FILE_ATTRIBUTE_TEMPORARY 256

#define PROGRESS_CONTINUE 0
#define PROGRESS_CANCEL 1
#define PROGRESS_STOP 2
#define PROGRESS_QUIET 3

// https://msdn.microsoft.com/en-us/library/windows/desktop/aa363858(v=vs.85).aspx
#define FILE_SHARE_READ 0x00000001
#define FILE_SHARE_WRITE 0x00000002
#define FILE_SHARE_DELETE 0x00000004

// https://msdn.microsoft.com/en-us/library/windows/desktop/aa364960(v=vs.85).aspx
#define FILE_TYPE_CHAR 0x0002
#define FILE_TYPE_DISK 0x0001
#define FILE_TYPE_PIPE 0x0003
#define FILE_TYPE_REMOTE 0x8000
#define FILE_TYPE_UNKNOWN 0x0000

// https://msdn.microsoft.com/en-gb/library/windows/desktop/aa364939(v=vs.85).aspx
#define DRIVE_UNKNOWN 0
#define DRIVE_NO_ROOT_DIR 1
#define DRIVE_REMOVABLE 2
#define DRIVE_FIXED 3
#define DRIVE_REMOTE 4
#define DRIVE_CDROM 5
#define DRIVE_RAMDISK 6

// http://www.jbox.dk/sanos/source/include/win32.h.html
#define GENERIC_READ                     0x80000000
#define GENERIC_WRITE                    0x40000000
#define GENERIC_EXECUTE                  0x20000000
#define GENERIC_ALL                      0x10000000

// http://www.jbox.dk/sanos/source/include/win32.h.html
#define CREATE_NEW                       1
#define CREATE_ALWAYS                    2
#define OPEN_EXISTING                    3
#define OPEN_ALWAYS                      4
#define TRUNCATE_EXISTING                5

// http://www.jbox.dk/sanos/source/include/win32.h.html
#define STD_INPUT_HANDLE                 ((DWORD)-10)
#define STD_OUTPUT_HANDLE                ((DWORD)-11)
#define STD_ERROR_HANDLE                 ((DWORD)-12)

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms686033(v=vs.85).aspx
#define ENABLE_PROCESSED_INPUT 0x0001
#define ENABLE_LINE_INPUT 0x0002
#define ENABLE_ECHO_INPUT 0x0004
#define ENABLE_MOUSE_INPUT 0x0010
#define ENABLE_WRAP_AT_EOL_OUTPUT 0x0002
#define ENABLE_PROCESSED_OUTPUT 0x0001

// https://github.com/gasgas4/NT_4.0_SourceCode/blob/84a03f73738328ea66034dca7cda79a857623720/nt4/private/windows/inc/shellapi.w
#define SEE_MASK_HASTITLE       0x00080000       
#define SEE_MASK_FLAG_DDEWAIT   0x00000100                        
#define SEE_MASK_NO_CONSOLE     0x00008000
#define SEE_MASK_NOCLOSEPROCESS 0x00000040

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
#define CREATE_NEW_CONSOLE 0x00000010
#define CREATE_NEW_PROCESS_GROUP 0x00000200
#define CREATE_NO_WINDOW 0x08000000

// https://webcache.googleusercontent.com/search?q=cache:xaaywBK_sCkJ:https://sourceforge.net/u/cstrauss/w32api/ci/f3077014e6186628344d580460bfafe4d3b52c9d/tree/include/winbase.h%3Fformat%3Draw+&cd=1&hl=en&ct=clnk&gl=uk
#define NORMAL_PRIORITY_CLASS 32
#define IDLE_PRIORITY_CLASS 64
#define HIGH_PRIORITY_CLASS 128
#define REALTIME_PRIORITY_CLASS 256

// https://webcache.googleusercontent.com/search?q=cache:xaaywBK_sCkJ:https://sourceforge.net/u/cstrauss/w32api/ci/f3077014e6186628344d580460bfafe4d3b52c9d/tree/include/winbase.h%3Fformat%3Draw+&cd=1&hl=en&ct=clnk&gl=uk
#define STARTF_USESHOWWINDOW 1
#define STARTF_USESHOWWINDOW 1

// http://www.lugaru.com/man/Other.Process.Primitives.html
#define SW_HIDE             0
#define SW_SHOWNORMAL       1
#define SW_SHOWMINIMIZED    2
#define SW_SHOWMAXIMIZED    3
#define SW_SHOWNOACTIVATE   4
#define SW_SHOW             5
#define SW_MINIMIZE         6
#define SW_SHOWMINNOACTIVE  7
#define SW_SHOWNA           8
#define SW_RESTORE          9

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms679351(v=vs.85).aspx
#define FORMAT_MESSAGE_FROM_HMODULE 0x00000800
#define FORMAT_MESSAGE_FROM_SYSTEM 0x00001000
#define FORMAT_MESSAGE_ARGUMENT_ARRAY 0x00002000
#define FORMAT_MESSAGE_IGNORE_INSERTS 0x00000200

// https://msdn.microsoft.com/en-us/library/windows/desktop/ms680621(v=vs.85).aspx
#define SEM_FAILCRITICALERRORS 0x0001

#if !defined(HINSTANCE_ERROR)
#define HINSTANCE_ERROR 32
#endif

#define IMAGE_SUBSYSTEM_WINDOWS_GUI 2
#define SCS_POSIX_BINARY 4

// FormatMessageWithArgs
// https://github.com/gasgas4/NT_4.0_SourceCode/blob/84a03f73738328ea66034dca7cda79a857623720/nt4/private/windows/shell/cabinet/message.c

// FormatMessage
// https://github.com/kerneltravel/longene_travel/blob/daa01b979536498ec2552db8e60abeef31894d72/wine-1.0-longene/dlls/kernel32/format_msg.c
// https://github.com/gasgas4/NT_4.0_SourceCode/blob/84a03f73738328ea66034dca7cda79a857623720/nt4/private/windows/base/client/message.c

#define UOI_NAME 2

#if defined(__GNUC__) || defined(__clang__)
#define FIELD_OFFSET(type, field) offsetof(type, field)
#else
#define FIELD_OFFSET(type, field) ((LONG)(INT_PTR)&(((type *)0)->field))
#endif

DWORD WINAPI GetEnvironmentVariable(
  LPCTSTR lpName,
  LPTSTR  lpBuffer,
  DWORD   nSize
);

DWORD WINAPI GetModuleFileName(
  _In_opt_ HMODULE hModule,
  _Out_    LPTSTR  lpFilename,
  _In_     DWORD   nSize
);

UINT WINAPI SetErrorMode(
  _In_ UINT uMode
);

BOOL WINAPI SetEnvironmentVariable(
  _In_     LPCTSTR lpName,
  _In_opt_ LPCTSTR lpValue
);

BOOL WINAPI CloseHandle(
  _In_ HANDLE hObject
);

BOOL WINAPI CreateProcess(
  _In_opt_    LPCTSTR               lpApplicationName,
  _Inout_opt_ LPTSTR                lpCommandLine,
  _In_opt_    LPSECURITY_ATTRIBUTES lpProcessAttributes,
  _In_opt_    LPSECURITY_ATTRIBUTES lpThreadAttributes,
  _In_        BOOL                  bInheritHandles,
  _In_        DWORD                 dwCreationFlags,
  _In_opt_    LPVOID                lpEnvironment,
  _In_opt_    LPCTSTR               lpCurrentDirectory,
  _In_        LPSTARTUPINFO         lpStartupInfo,
  _Out_       LPPROCESS_INFORMATION lpProcessInformation
);

BOOL WINAPI GetExitCodeProcess(
  _In_  HANDLE  hProcess,
  _Out_ LPDWORD lpExitCode
);

DWORD WINAPI WaitForSingleObject(
  _In_ HANDLE hHandle,
  _In_ DWORD  dwMilliseconds
);

BOOL WINAPI DuplicateHandle(
  _In_  HANDLE   hSourceProcessHandle,
  _In_  HANDLE   hSourceHandle,
  _In_  HANDLE   hTargetProcessHandle,
  _Out_ LPHANDLE lpTargetHandle,
  _In_  DWORD    dwDesiredAccess,
  _In_  BOOL     bInheritHandle,
  _In_  DWORD    dwOptions
);

BOOL ShellExecuteEx(
  _Inout_ SHELLEXECUTEINFO *pExecInfo
);

BOOL WINAPI TerminateProcess(
  _In_ HANDLE hProcess,
  _In_ UINT   uExitCode
);

SIZE_T WINAPI VirtualQuery(
  _In_opt_ LPCVOID                   lpAddress,
  _Out_    LPVOID lpBuffer,
  _In_     SIZE_T                    dwLength
);

DWORD WINAPI FormatMessage(
  _In_     DWORD   dwFlags,
  _In_opt_ LPCVOID lpSource,
  _In_     DWORD   dwMessageId,
  _In_     DWORD   dwLanguageId,
  _Out_    LPTSTR  lpBuffer,
  _In_     DWORD   nSize,
  _In_opt_ va_list *Arguments
);

void WINAPI OutputDebugStringA(
  _In_opt_ LPCTSTR lpOutputString
);


#include "_locale.h"
#include "_time.h"
#include "_memory.h"
#include "_file.h"

#endif
