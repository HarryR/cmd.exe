# Portable cmd.exe

```
$ ./cmd.exe
Microsoft(R) Windows 95(TM)
(C) Copyright 1985-1996 Microsoft Corp.

C:\home\user\Projects\cmd.exe>dir C:\
 Volume in drive C is C
 Volume Serial Number is 1234-5678

 Directory of C:\

11/21/16  09:05a        <DIR>          .
11/21/16  09:05a        <DIR>          ..
11/18/16  05:04p        <DIR>          bin
11/21/16  09:07a        <DIR>          boot
11/17/16  10:59a        <DIR>          cdrom
11/22/16  08:54a        <DIR>          dev
11/23/16  03:07p        <DIR>          etc
11/17/16  02:29p        <DIR>          home
11/21/16  09:07a            38,824,693 initrd.img
11/18/16  05:10p            38,339,082 initrd.img.old
11/20/16  11:54p        <DIR>          lib
11/17/16  03:19p        <DIR>          lib64
11/17/16  10:55a        <DIR>          lost+found
11/17/16  11:24a        <DIR>          media
07/19/16  08:42p        <DIR>          mnt
11/22/16  02:23p        <DIR>          opt
11/22/16  08:52a        <DIR>          proc
11/18/16  10:43a        <DIR>          root
11/23/16  03:07p        <DIR>          run
11/21/16  09:02a        <DIR>          sbin
06/29/16  08:13p        <DIR>          snap
07/19/16  08:42p        <DIR>          srv
11/22/16  08:52a        <DIR>          sys
11/23/16  03:56p        <DIR>          tmp
07/19/16  08:48p        <DIR>          usr
07/19/16  08:54p        <DIR>          var
10/26/16  10:27p             7,060,896 vmlinuz
11/17/16  10:58a             7,047,520 vmlinuz.old
              28 File(s)     91,385,291 bytes
                                      0 bytes free

C:\home\user\Projects\cmd.exe>ver

Windows 95 Version 4.0  

C:\home\user\Projects\cmd.exe>
```

# Why?

Because my soul aim in life is to have a Windows NT compatible CMD shell when I login to my Unix boxen. This is my Dark Souls. Previously I used Plan9's `rc`, then Python, then `scsh`. Now it's time for the ultimate level of massochism and technological fuckery. Now, I would have ported VMS's DCL to POSIX, but I couldn't find the source code, nor do I feel like writing a BLISS compiler.

## Porting Method

 1. Remove small chunks of code which we know aren't applicaple
 2. Identify and add missing defines / typedefs
 3. Fix minor / trivial compile errors
 4. Implement minor / trivial API stubs (e.g. `HeapFree`, `SetFilePointer`)
 5. Identify APIs which can be easily implemented or replaced
 6. Implement stubs for other APIs, `abort()` / TRAP them
 7. Error handling
 8. Rewrite other APIs as necessary
 9. Verify API functionality against native Windows
 10. Test CMD functionality...
 11. Goto 8

## Troublesome areas

 * SearchPath - translate from Windows `PATH` to POSIX `PATH`
 * SetConsoleCtrlHandler - replicate with `signal()`
 * FindFirstFile etc. - replace with `readdir_r`
 * ShellExecute / DuplicateHandle / CreateProcess / GetExitCodeProcess / TerminateProcess / CloseHandle - process lifecycle, pipes, redirection, general shell stuff
 * GetEnvironmentStrings - Works differently to `eviron`
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

