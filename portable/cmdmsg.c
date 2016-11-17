#include "cmd.h"
const cmdmsg_t g_cmdmsg[] = {
{0x00002328L, "MSG_RESPONSE_DATA", "Y N\n"}
, {0x00002329L, "MSG_BAD_PARM1", "An incorrect parameter was\nentered for the command.\n"}
, {0x0000232aL, "MSG_BAD_SYNTAX", "The syntax of the command is incorrect.\n"}
, {0x0000232bL, "MSG_STRIKE_ANY_KEY", "Press any key to continue . . . %0\n"}
, {0x0000232cL, "MSG_CMD_DELETE", "%1, Delete (Y/N)? %0\n"}
, {0x0000232dL, "MSG_COM_SEARCH_DIR_BAD", "The system cannot find the\ncommand processor in the path specified.\n"}
, {0x0000232eL, "MSG_REN_INVAL_PATH_FILENAME", "The system cannot accept the path\nor file name requested.\n"}
, {0x0000232fL, "MSG_INVALID_DATE", "The system cannot accept the date entered.\n"}
, {0x00002330L, "MSG_NO_BAT_LABEL", "No batch label specified to GOTO command.\n"}
, {0x00002331L, "MSG_DIR_BAD_COMMAND_OR_FILE", "The name specified is not recognized as an\ninternal or external command, operable program or batch file.\n"}
, {0x00002332L, "MSG_REN_INVALID_TIME", "The system cannot accept the time entered.\n"}
, {0x00002333L, "MSG_BAD_DOS_VER", "The application program is not compatible\nwith the version of the operating system being used.\n"}
, {0x00002334L, "MSG_COMM_VER", "Microsoft(R) Windows %1(TM)\n(C) Copyright 1985-1996 Microsoft Corp.\n"}
, {0x00002335L, "MSG_C", "^C\n"}
, {0x00002336L, "MSG_FILES_COPIED", "%1 file(s) copied.\n"}
, {0x00002337L, "MSG_CURRENT_DATE", "The current date is: %0\n"}
, {0x00002338L, "MSG_CURRENT_TIME", "The current time is: %0\n"}
, {0x00002339L, "MSG_DIR_OF", " Directory of %1\n\n"}
, {0x0000233aL, "MSG_OUT_OF_ENVIRON_SPACE", "The system is out of environment space.\n"}
, {0x0000233bL, "MSG_INVALID_DOS_FILENAME", " The file name entered is not valid in DOS mode.\n"}
, {0x0000233cL, "MSG_EXEC_FAILURE", "The system cannot execute the specified program.\n"}
, {0x0000233dL, "MSG_FILES_FREE", "     %1 File(s)   %2 bytes free\n"}
, {0x0000233eL, "MSG_FILES_ONLY", "     %1 File(s).\n"}
, {0x0000233fL, "MSG_LINES_TOO_LONG", "The input line is too long.\n"}
, {0x00002340L, "MSG_CONT_LOST_BEF_COPY", "The contents of the target file\nwere lost.\n"}
, {0x00002341L, "MSG_INSRT_DISK_BAT", "Insert the diskette that contains the batch file\nand press any key when ready. %0\n"}
, {0x00002342L, "MSG_ENTER_NEW_DATE", "Enter the new date: (mm-dd-yy) %0\n"}
, {0x00002343L, "MSG_ENTER_NEW_TIME", "Enter the new time: %0\n"}
, {0x00002344L, "MSG_RDR_HNDL_CREATE", "The handle could not be duplicated\nduring redirection of handle %1.\n"}
, {0x00002345L, "MSG_ECHO_OFF", "ECHO is off.\n"}
, {0x00002346L, "MSG_ECHO_ON", "ECHO is on.\n"}
, {0x00002347L, "MSG_VERIFY_OFF", "VERIFY is off.\n"}
, {0x00002348L, "MSG_VERIFY_ON", "VERIFY is on.\n"}
, {0x00002349L, "MSG_CANNOT_COPIED_ONTO_SELF", "The file cannot be copied onto itself.\n"}
, {0x0000234aL, "MSG_SYNERR_GENL", "%1 was unexpected at this time.\n"}
, {0x0000234bL, "MSG_TOP_LEVEL_PROCESS_CAN", "CMD.EXE has halted. %0\n"}
, {0x0000234cL, "MSG_PID_IS", "The Process Identification Number is %1.\n"}
, {0x0000234dL, "MSG_DUP_FILENAME_OR_NOT_FD", "A duplicate file name exists, or the file\ncannot be found.\n"}
, {0x0000234eL, "MSG_ARE_YOU_SURE", "%1, Are you sure (Y/N)? %0\n"}
, {0x0000234fL, "MSG_TOKEN_TOO_LONG", "The following character string is too long:\n%1\n"}
, {0x00002350L, "MSG_MS_DOS_VERSION", "Windows %1 Version %2.%3 %0\n"}
, {0x00002351L, "MSG_PIPE_FAILURE", "The handle could not be duplicated during\na pipe operation.\n"}
, {0x00002352L, "MSG_MS_MORE", "More? %0\n"}
, {0x00002353L, "MSG_REAL_MODE_ONLY", "The system cannot complete the process.\n"}
, {0x00002354L, "MSG_TYPE_FILENAME", "\n%1\n\n\n"}
, {0x00002355L, "MSG_INVALID_INPUT", "Unable to read from input.\n"}
, {0x0000235bL, "MSG_DR_VOL_SERIAL", " Volume Serial Number is %1\n"}
, {0x0000235cL, "MSG_DIR_EXISTS", "A subdirectory or file %1 already exists.\n"}
, {0x0000235dL, "MSG_ERR_PROC_ARG", "Error occurred while processing: %1.\n"}
, {0x0000235eL, "MSG_HAS_NO_LABEL", " Volume in drive %1 has no label.\n"}
, {0x0000235fL, "MSG_DR_VOL_LABEL", " Volume in drive %1 is %2\n"}
, {0x00002360L, "MSG_KEYS_ON", "KEYS is on.\n"}
, {0x00002361L, "MSG_KEYS_OFF", "KEYS is off.\n"}
, {0x00002362L, "MSG_START_INVALID_PARAMETER", "The system cannot accept the START command parameter %1.\n"}
, {0x00002363L, "MSG_CMD_FILE_NOT_FOUND", "The system cannot find the file %1.\n"}
, {0x00002364L, "MSG_CMD_INVAL_PIPE", "The process tried to write to a nonexistent pipe.\n"}
, {0x00002365L, "MSG_CMD_CANT_FRGRND", "The system cannot start the session in the foreground.\n"}
, {0x00002366L, "MSG_CMD_SYS_ERR", "\nA non-recoverable error occurred.\nThe process ended.\n"}
, {0x00002367L, "MSG_CMD_DIV_0", "\nThe system detected a divide by zero error.\n"}
, {0x00002368L, "MSG_CMD_SOFT_ERR", "\nThe process has stopped.  The software\ndiagnostic code (trap number) is %1.\n"}
, {0x00002369L, "MSG_CMD_COPROC", "\nThe process ended when it tried to use\na non-existent math processor.\n"}
, {0x0000236aL, "MSG_CMD_KILLED", "The external process was canceled by a Ctrl+Break or another process.\n"}
, {0x0000236bL, "MSG_CMD_NOT_RECOGNIZED", "\"%1\" is not a recognized device.\n"}
, {0x0000236cL, "MSG_CMD_BATCH_FILE_MISSING", "The batch file cannot be found.\n"}
, {0x0000236eL, "MSG_FILES_MOVED", "%1 file(s) moved.\n"}
, {0x0000236fL, "MSG_TRAPC", "A program attempted to reference storage outside the\nlimits of a stack segment.  The program was ended.\n\n%1\n"}
, {0x00002370L, "MSG_UNEXPEC_ERROR_ENC", "Error %1 encountered an unexpected end of file\non the redirected input. The process has stopped.\n"}
, {0x00002371L, "MSG_LITERAL_TEXT", "%1%0\n"}
, {0x00002372L, "MSG_NOT_IMPLEMENTED", "Command not implemented.\n"}
, {0x00002373L, "MSG_DIR", "<DIR>       %0\n"}
, {0x00002374L, "MSG_NO_MEMORY", "Out of memory.\n"}
, {0x00002375L, "MSG_INVALID_SWITCH", "Invalid switch - \"%1\".\n"}
, {0x00002376L, "MSG_PARAMETER_FORMAT_NOT_CORRECT", "Parameter format not correct - \"%1\".\n"}
, {0x00002377L, "MSG_ERROR_IN_DIRCMD", "(Error occurred in environment variable)\n"}
, {0x00002378L, "MSG_FILES_COUNT_FREE", "     %1 File(s) %2 bytes\n"}
, {0x00002379L, "MSG_FILES_TOTAL_FREE", "                      %1 bytes free\n"}
, {0x0000237aL, "MSG_FILE_TOTAL", "     Total Files Listed:\n"}
, {0x0000237bL, "MSG_BATCH_TERM", "Terminate batch job (Y/N)? %0\n"}
, {0x0000237cL, "MSG_BAD_CURDIR", "The current directory is invalid.\n"}
, {0x0000237dL, "MSG_HELP_CHDIR", "Displays the name of or changes the current directory.\n\nCHDIR [/D] [drive:][path]\nCHDIR [..]\nCD [/D] [drive:][path]\nCD [..]\n\n  ..   Specifies that you want to change to the parent directory.\n\nType CD drive: to display the current directory in the specified drive.\nType CD without parameters to display the current drive and directory.\n\nUse the /D switch to change current drive in addition to changing current\ndirectory for a drive.\n"}
, {0x0000237eL, "MSG_HELP_CLS", "Clears the screen.\n\nCLS\n"}
, {0x0000237fL, "MSG_HELP_COPY", "Copies one or more files to another location.\n\nCOPY [/A | /B] source [/A | /B] [+ source [/A | /B] [+ ...]] [destination\n  [/A | /B]] [/V] [/N]\n\n  source       Specifies the file or files to be copied.\n  /A           Indicates an ASCII text file.\n  /B           Indicates a binary file.\n  destination  Specifies the directory and/or filename for the new file(s).\n  /V           Verifies that new files are written correctly.\n  /N           Uses short filename, if available, when copying a file with a\n               non-8dot3 name.\n  /Z           Copies networked files in restartable mode.\n\nTo append files, specify a single file for destination, but multiple files\nfor source (using wildcards or file1+file2+file3 format).\n"}
, {0x00002380L, "MSG_HELP_DATE", "Displays or sets the date.\n\nDATE [date]\n\nType DATE without parameters to display the current date setting and\na prompt for a new one.  Press ENTER to keep the same date.\n"}
, {0x00002381L, "MSG_HELP_DEL_ERASE", "Deletes one or more files.\n\nDEL [/P] [/F] [/S] [/Q] [/A[[:]attributes]] [[drive:][path]filename\nERASE [/P] [/F] [/S] [/Q] [/A[[:]attributes]] [[drive:][path]filename\n\n  [drive:][path]filename\n                Specifies the file(s) to delete.  Specify multiple\n                files by using wildcards.\n  /P            Prompts for confirmation before deleting each file.\n  /F            Force deleting of read-only files.\n  /S            Delete specified files from all subdirectories.\n  /Q            Quiet mode, do not ask if ok to delete on global wildcard\n  /A            Selects files to delete based on attributes\n  attributes    R  Read-only files            S  System files\n                H  Hidden files               A  Files ready for archiving\n                -  Prefix meaning not\n"}
, {0x00002382L, "MSG_HELP_DIR", "Displays a list of files and subdirectories in a directory.\n\nDIR [drive:][path][filename] [/P] [/W] [/D] [/A[[:]attributes]]\n  [/O[[:]sortorder]] [/T[[:]timefield]] [/S] [/B] [/L] [/N] [/X] [/C]\n\n  [drive:][path][filename]\n              Specifies drive, directory, and/or files to list.\n\n  /P          Pauses after each screenful of information.\n  /W          Uses wide list format.\n  /D          Same as wide but files are list sorted by column.\n  /A          Displays files with specified attributes.\n  attributes   D  Directories                R  Read-only files\n               H  Hidden files               A  Files ready for archiving\n               S  System files               -  Prefix meaning not\n  /O          List by files in sorted order.\n  sortorder    N  By name (alphabetic)       S  By size (smallest first)\n               E  By extension (alphabetic)  D  By date & time (earliest first)\n               G  Group directories first    -  Prefix to reverse order\n  /T          Controls which time field displayed or used for sorting\n  timefield   C  Creation\n              A  Last Access\n              W  Last Written\n  /S          Displays files in specified directory and all subdirectories.\n  /B          Uses bare format (no heading information or summary).\n  /L          Uses lowercase.\n  /N          New long list format where filenames are on the far right.\n  /X          This displays the short names generated for non-8dot3 file\n              names.  The format is that of /N with the short name inserted\n              before the long name. If no short name is present, blanks are\n              displayed in its place.\n  /C          Display the thousand separator in file sizes.  This is the\n              default.  Use /-C to disable display of separator.\n\nSwitches may be preset in the DIRCMD environment variable.  Override\npreset switches by prefixing any switch with - (hyphen)--for example, /-W.\n"}
, {0x00002383L, "MSG_HELP_EXIT", "Quits the CMD.EXE program (command interpreter).\n\nEXIT\n"}
, {0x00002384L, "MSG_HELP_MKDIR", "Creates a directory.\n\nMKDIR [drive:]path\nMD [drive:]path\n"}
, {0x00002385L, "MSG_HELP_PATH", "Displays or sets a search path for executable files.\n\nPATH [[drive:]path[;...][;%%PATH%%]\nPATH ;\n\nType PATH ; to clear all search-path settings and direct cmd.exe to search\nonly in the current directory.\nType PATH without parameters to display the current path.\nIncluding %%PATH%% in the new path setting causes the old path to be appended\nto the new setting.\n"}
, {0x00002386L, "MSG_HELP_PROMPT", "Changes the cmd.exe command prompt.\n\nPROMPT [text]\n\n  text    Specifies a new command prompt.\n\nPrompt can be made up of normal characters and the following special codes:\n\n  $A   & (Ampersand)\n  $B   | (pipe)\n  $C   ( (Left parenthesis)\n  $D   Current date\n  $E   Escape code (ASCII code 27)\n  $F   ) (Right parenthesis)\n  $G   > (greater-than sign)\n  $H   Backspace (erases previous character)\n  $L   < (less-than sign)\n  $N   Current drive\n  $P   Current drive and path\n  $Q   = (equal sign)\n  $S     (space)\n  $T   Current time\n  $V   Windows NT version number\n  $_   Carriage return and linefeed\n  $$   $ (dollar sign)\n"}
, {0x00002387L, "MSG_HELP_RMDIR", "Removes (deletes) a directory.\n\nRMDIR [/S] [/Q] [drive:]path\nRD [/S] [/Q] [drive:]path\n\n    /S      Removes all directories and files in the specified directory\n            in addition to the directory itself.  Used to remove a directory\n            tree.\n\n    /Q      Quiet mode, do not ask if ok to remove a directory tree with /S\n"}
, {0x00002388L, "MSG_HELP_RENAME", "Renames a file or files.\n\nRENAME [drive:][path]filename1 filename2.\nREN [drive:][path]filename1 filename2.\n\nNote that you cannot specify a new drive or path for your destination file.\n"}
, {0x00002389L, "MSG_HELP_SET", "Displays, sets, or removes cmd.exe environment variables.\n\nSET [variable=[string]]\n\n  variable  Specifies the environment-variable name.\n  string    Specifies a series of characters to assign to the variable.\n\nType SET without parameters to display the current environment variables.\n"}
, {0x0000238aL, "MSG_HELP_TIME", "Displays or sets the system time.\n\nTIME [time]\n\nType TIME with no parameters to display the current time setting and a prompt\nfor a new one.  Press ENTER to keep the same time.\n"}
, {0x0000238bL, "MSG_HELP_TYPE", "Displays the contents of a text file or files.\n\nTYPE [drive:][path]filename\n"}
, {0x0000238cL, "MSG_HELP_VER", "Displays the Windows NT version.\n\nVER\n"}
, {0x0000238dL, "MSG_HELP_VERIFY", "Tells cmd.exe whether to verify that your files are written correctly to a\ndisk.\n\nVERIFY [ON | OFF]\n\nType VERIFY without a parameter to display the current VERIFY setting.\n"}
, {0x0000238eL, "MSG_HELP_VOL", "Displays the disk volume label and serial number, if they exist.\n\nVOL [drive:]\n"}
, {0x0000238fL, "MSG_HELP_CALL", "Calls one batch program from another.\n\nCALL [drive:][path]filename [batch-parameters]\n\n  batch-parameters   Specifies any command-line information required by the\n                     batch program.\n"}
, {0x00002390L, "MSG_HELP_REM", "Records comments (remarks) in a batch file or CONFIG.SYS.\n\nREM [comment]\n"}
, {0x00002391L, "MSG_HELP_PAUSE", "Suspends processing of a batch program and displays the message\n    Press any key to continue . . . %0\n\nPAUSE\n"}
, {0x00002392L, "MSG_HELP_ECHO", "Displays messages, or turns command-echoing on or off.\n\n  ECHO [ON | OFF]\n  ECHO [message]\n\nType ECHO without parameters to display the current echo setting.\n"}
, {0x00002393L, "MSG_HELP_GOTO", "Directs cmd.exe to a labeled line in a batch program.\n\nGOTO label\n\n  label   Specifies a text string used in the batch program as a label.\n\nYou type a label on a line by itself, beginning with a colon.\n"}
, {0x00002394L, "MSG_HELP_SHIFT", "Changes the position of replaceable parameters in a batch file.\n\nSHIFT [/n]\n"}
, {0x00002395L, "MSG_HELP_IF", "Performs conditional processing in batch programs.\n\nIF [NOT] ERRORLEVEL number command\nIF [NOT] string1==string2 command\nIF [NOT] EXIST filename command\n\n  NOT               Specifies that Windows NT should carry out the command only\n                    if the condition is false.\n  ERRORLEVEL number Specifies a true condition if the last program run returned\n                    an exit code equal to or greater than the number specified.\n  command           Specifies the command to carry out if the condition is\n                    met.\n  string1==string2  Specifies a true condition if the specified text strings\n                    match.\n  EXIST filename    Specifies a true condition if the specified filename\n                    exists.\n"}
, {0x00002396L, "MSG_HELP_FOR", "Runs a specified command for each file in a set of files.\n\nFOR %%variable IN (set) DO command [command-parameters]\n\n  %%variable Specifies a replaceable parameter.\n  (set)      Specifies a set of one or more files.  Wildcards may be used.\n  command    Specifies the command to carry out for each file.\n  command-parameters\n             Specifies parameters or switches for the specified command.\n\nTo use the FOR command in a batch program, specify %%%%variable instead\nof %%variable Variable names are case sensitive, so %%i is different\nfrom %%I.\n"}
, {0x00002397L, "MSG_HELP_START", "Starts a separate window to run a specified program or command.\n\nSTART [\"title\"] [/Dpath] [/I] [/MIN] [/MAX] [/SEPARATE | /SHARED]\n      [/LOW | /NORMAL | /HIGH | /REALTIME] [/WAIT] [/B] [command/program] [parameters]\n\n    \"title\"     Title to display in  window title bar.\n    path        Starting directory\n    I           The new environment will be the original environment passed\n                to the cmd.exe and not the current environment.\n    MIN         Start window minimized\n    MAX         Start window maximized\n    SEPARATE    Start 16-bit Windows program in separate memory space\n    SHARED      Start 16-bit Windows program in shared memory space\n    LOW         Start application in the IDLE priority class\n    NORMAL      Start application in the NORMAL priority class\n    HIGH        Start application in the HIGH priority class\n    REALTIME    Start application in the REALTIME priority class\n    WAIT        Start application and wait for it to terminate\n    B           Start application without creating a new window. The\n                application has ^C handling ignored. Unless the application\n                enables ^C processing, ^Break is the only way to interrupt the\n                application\n    command/program\n                If it is an internal cmd command or a batch file then\n                the command processor is run with the /K switch to cmd.exe.\n                This means that the window will remain after the command\n                has been run.\n\n                If it is not an internal cmd command or batch file then\n                it is a program and will run as either a windowed application\n                or a console application.\n\n    parameters  These are the parameters passed to the command/program\n\n"}
, {0x00002398L, "MSG_HELP_BREAK", "Sets or Clears Extended CTRL+C checking on DOS system\n\nThis is present for Compatibility with DOS systems. It has no effect\nunder Windows NT.\n"}
, {0x00002399L, "MSG_HELP_CMD", "Starts a new instance of the Windows/NT command interpreter\n\nCMD [/X | /Y] [/A | /U] [/Q] [[/C | /K] string]\n\n/C      Carries out the command specified by string and then terminates\n/K      Carries out the command specified by string but remains\n/Q      Turns the echo off\n/A      Causes the output of internal commands to a pipe or file to be ANSI\n/U      Causes the output of internal commands to a pipe or file to be Unicode\n/T:fg   Sets the foreground/background colors (see COLOR /? for more info)\n/X      Enable extensions to the Windows NT version of CMD.EXE\n/Y      Disable extensions to the Windows NT version of CMD.EXE\n\nNote that multiple commands separated by the command separator '&&'\nare accepted for string if surrounded by quotes\n\n"}
, {0x00002710L, "MSG_TOO_MANY_PARAMETERS", "Too many parameters - %1\n"}
, {0x00002714L, "MSG_HELP_SETLOCAL", "Begins localization of environment changes in a batch file.\nEnvironment changes made after SETLOCAL has been issued are\nlocal to the batch file.  ENDLOCAL must be issued to\nrestore the previous settings.\n\nSETLOCAL\n"}
, {0x00002715L, "MSG_HELP_ENDLOCAL", "Ends localization of environment changes in a batch file.\nEnvironment changes made after ENDLOCAL has been issued are\nnot local to the batch file; the previous settings are not\nrestored on termination of the batch file.\n\nENDLOCAL\n"}
, {0x00002716L, "MSG_HELP_TITLE", "Sets the window title for the command prompt window.\n\nTITLE [string]\n\n  string       Specifies the title for the command prompt window.\n"}
, {0x00002717L, "MSG_HELP_APPEND", "Allows programs to open data files in specified directories as if they were in\nthe current directory.\n\nAPPEND [[drive:]path[;...]] [/X[:ON | :OFF]] [/PATH:ON | /PATH:OFF] [/E]\nAPPEND ;\n\n  [drive:]path Specifies a drive and directory to append.\n  /X:ON        Applies appended directories to file searches and\n               application execution.\n  /X:OFF       Applies appended directories only to requests to open files.\n               /X:OFF is the default setting.\n  /PATH:ON     Applies the appended directories to file requests that already\n               specify a path.  /PATH:ON is the default setting.\n  /PATH:OFF    Turns off the effect of /PATH:ON.\n  /E           Stores a copy of the appended directory list in an environment\n               variable named APPEND.  /E may be used only the first time\n               you use APPEND after starting up your system.\n\nType APPEND ; to clear the appended directory list.\nType APPEND without parameters to display the appended directory list.\n"}
, {0x00002718L, "MSG_HELP_MOVE", "Moves one or more files from one directory to another directory.\n\nMOVE [Source] [Target]\n\n  source       Specifies the path and name of the file(s) to move.\n  target       Specifies the path and name to move file(s) to.\n"}
, {0x00002719L, "MSG_HELP_PUSHDIR", "Stores the current directory for use by the POPD command, then\nchanges to the specified directory.\n\nPUSHD [path | ..]\n\n  path        Specifies the directory to make the current directory.\n"}
, {0x0000271aL, "MSG_HELP_POPDIR", "Changes to the directory stored by the PUSHD command.\n\nPOPD\n\n"}
, {0x0000271bL, "MSG_FILE_NAME_PRECEEDING_ERROR", "%1 - %0\n"}
, {0x0000271cL, "MSG_MAX_SETLOCAL", "Maximum setlocal recursion level reached.\n"}
, {0x0000271dL, "MSG_ENTER_JAPAN_DATE", "Enter the new date: (yy-mm-dd) %0\n"}
, {0x0000271eL, "MSG_ENTER_DEF_DATE", "Enter the new date: (dd-mm-yy) %0\n"}
, {0x00002721L, "MSG_RDR_HNDL_OPEN", "The handle could not be opened\nduring redirection of handle %1.\n"}
, {0x00002722L, "MSG_PROGRESS", "%r%1%% copied %0\n"}
, {0x00002723L, "MSG_HELP_COLOR", "Sets the default console foreground and background colors.\n\nCOLOR [attr]\n\n  attr        Specifies color attribute of console output\n\nColor attributes are specified by TWO hex digits -- the first\ncorresponds to the background; the second the foreground.  Each digit\ncan be any of the following values:\n\n    0 = Black       8 = Gray\n    1 = Blue        9 = Light Blue\n    2 = Green       A = Light Green\n    3 = Aqua        B = Light Aqua\n    4 = Red         C = Light Red\n    5 = Purple      D = Light Purple\n    6 = Yellow      E = Light Yellow\n    7 = White       F = Bright White\n\nIf no argument is given, this command restores the color to what it was\nwhen CMD.EXE started.  This value either comes from the current console\nwindow, the /T command line switch or from the DefaultColor registry\nvalue.\n\nThe COLOR command sets ERRORLEVEL to 1 if an attempt is made to execute\nthe COLOR command with a foreground and background color that are the\nsame.\n\nExample: \"COLOR fc\" produces light red on bright white\n"}
, {0x00002724L, "MSG_MAX_PATH_EXCEEDED", "Maximum path length exceeded - %1\n"}
, {0, "_END_", "_END_"}
};
