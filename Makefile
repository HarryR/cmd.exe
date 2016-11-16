CFLAGS = -Iportable -I. -ggdb -O0

SOURCES=portable/compat.c \
	portable/_locale.c \
	portable/_time.c \
	portable/_memory.c \
	portable/_ltoa.c \
	portable/_file.c \
	cbatch.c \
	cchcp.c \
	cclock.c \
	cdata.c \
	cdebug.c \
	cenv.c \
	cext.c \
	cfile.c \
	cinfo.c \
	cinit.c \
	ckeys.c \
	clex.c \
	cmd.c \
	cmem.c \
	cop.c \
	console.c \
	cother.c \
	cparse.c \
	cpath.c \
	cpparse.c \
	cpwork.c \
	csig.c \
	ctools1.c \
	ctools2.c \
	ctools3.c \
	del.c   \
	dir.c \
	display.c \
	ffirst.c \
	hstoi.c \
	start.c \
	string.c \
	tree.c  \
	readcon.c \
	complete.c
#	uipriv.c \

OBJECTS = $(SOURCES:.c=.o)

all: cmd.exe

cmd.exe: $(OBJECTS)
	$(CC) -o $@ $+

clean:
	rm -f $(OBJECTS) cmd.exe
