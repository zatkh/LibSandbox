CC = gcc
CFLAGS = -fPIC -nostdlib -I.

OBJS = linux_close.o linux_exit.o linux_open.o linux_read.o linux_write.o \
	linux_mmap.o linux_munmap.o linux_stat.o memcpy.o \
	print.o errno.o strtoul.o file_size.o string.o linux_mprotect.o \
	linux_sbrk.o

all: minc.a

minc.a: $(OBJS)
	ar rcs minc.a $(OBJS)

linux_close.o: linux_close.c minc.h
linux_exit.o: linux_exit.c minc.h
linux_open.o: linux_open.c minc.h
linux_read.o: linux_read.c minc.h
linux_write.o: linux_write.c minc.h
linux_stat.o: linux_stat.c minc.h
linux_sbrk.o: linux_sbrk.c minc.h
linux_mmap.o: linux_mmap.c 
linux_mprotect.o: linux_mprotect.c  minc.h
linux_munmap.o: linux_munmap.c minc.h
print.o: print.c minc.h
errno.o: errno.c minc.h
strtoul.o: strtoul.c minc.h
file_size.o: file_size.c minc.h
string.o: string.c minc.h
memcpy.o: memcpy.c minc.h

clean:
	-rm -rf *.o *.a *core
