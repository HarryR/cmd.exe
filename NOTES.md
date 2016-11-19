# Why?

Because my soul aim in life is to have a Windows NT compatible CMD shell when I login to my Unix boxen. This is my Dark Souls. Previously I used Plan9's `rc`, then Python, then `scsh`. Now it's time for the ultimate level of massochism and technological fuckery. Now, I would have ported VMS's DCL to POSIX, but I couldn't find the source code.

## Porting Method

 1. Remove small chunks of code which we know aren't applicaple
 2. Identify and add missing defines / typedefs
 3. Fix minor / trivial compile errors
 4. Implement minor / trivial API stubs (e.g. `HeapFree`, `SetFilePointer`)
 5. Identify APIs which can be easily implemented or replaced
 6. Implement stubs for other APIs, `abort()` / TRAP them
 7. Error handling
 8. Rewrite other APIs as necessary

## Troublesome areas

 * SearchPath - translate from Windows `PATH` to POSIX `PATH`
 * SetConsoleCtrlHandler - replicate with `signal()`
 * FindFirstFile etc. - replace with `readdir_r`
 * ShellExecute / DuplicateHandle / CreateProcess / GetExitCodeProcess / TerminateProcess / CloseHandle - process lifecycle, pipes, redirection, general shell stuff
 * GetEnvironmentStrings - 
 * FormatMessage - No POSIX equivalent... must be emulated
 * Console, DOS vs NT vs Win95 vs Sanity. - Can be mostly emulated with readline, ncurses, termcap - reading line at a time vs char at a time vs N-sized buf at a time

## Really troublesome areas

 * All of the path related functions rely on having drive letters and backslashes, so that means whenever we provide a compatibility layer we have to translate from C:\DERP to /DERP etc.

## Cruft Removed

 * ChkStack - check the stack usage
 * Copen_Work - Removed, use native open()
 * PrtErr - replaced with strerror?
 * InitializeDbcsLeadCharTable
 * ReadBufFromConsole
 * wide chars / unicode
 * Win32 console

