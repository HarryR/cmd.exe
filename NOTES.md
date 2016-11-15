# Porting Method

 1. Remove small chunks of code which we know aren't applicaple
 2. Identify and add missing defines / typedefs
 3. Fix minor / trivial compile errors
 4. Implement minor / trivial API stubs (e.g. `HeapFree`, `SetFilePointer`)
 5. Identify APIs which can be easily implemented or replaced
 6. Rewrite code which has no

## Cruft Removed

 * ChkStack - check the stack usage
 * Copen_Work - Removed, use native open()
 * PrtErr - replaced with strerror
 * InitializeDbcsLeadCharTable
 * ReadBufFromConsole
 * wide chars
 * Win32 console

## Cruft to Add

 * GetFullPathName - realpath
 * GetLastError ?
 * MoveFile - https://msdn.microsoft.com/en-us/library/windows/desktop/aa365239(v=vs.85).aspx
 * FindFirstFile - https://msdn.microsoft.com/en-us/library/windows/desktop/aa364418(v=vs.85).aspx
 * FindNextFile
 * SetLastError
CloseHandle
CopyFile
CreateDirectory
CreateFile
CreateProcess
DebugBreak
DuplicateHandle
FindClose
FindFirstFile
FindNextFile
FlushConsoleInputBuffer
FlushFileBuffers
FormatMessage
GetBinaryType
GetCommandLine
GetConsoleMode
GetConsoleTitle
GetCurrentDirectory
GetCurrentThreadId
GetDiskFreeSpace
GetDriveType
GetEnvironmentStrings
GetEnvironmentVariable
GetExitCodeProcess
GetFileAttributes
GetFileType
GetFullPathName
GetLastError
GetModuleFileName
GetModuleHandle
GetProcAddress
GetProcessSubsystemType
GetProcessWindowStation
GetStdHandle
GetThreadDesktop
GetUserObjectInformation
GetVersion
GetVolumeInformation
GetWindowsDirectory
HeapSize
MoveFile
MultiByteToWideChar
ReadBufFromConsole
RemoveDirectory
SearchPath
SetColor
SetConsoleCtrlHandler
SetConsoleMode
SetConsoleTitle
SetCurrentDirectory
SetEnvironmentVariable
SetErrorMode
SetFileApisToOEM
SetFileAttributes
SetFileTime
SetLastError
SetLocalTime
ShellExecuteEx
TerminateProcess
UInt32x32To64
VirtualAlloc
VirtualFree
VirtualQuery
WNetCancelConnection2
WNetGetConnection
WaitForSingleObject
WriteConsole
WriteFile
_close
_dup
_dup2
_open_osfhandle
_pipe
_setmode
_tcslwr
_tell
_vsntprintf
lstrcmpi
wsprintf
