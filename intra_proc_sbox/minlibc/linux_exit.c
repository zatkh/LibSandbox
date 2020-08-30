#include <sys/syscall.h>
#include <minc.h>

void linux_exit(int code)
{
	asm volatile ("syscall" : : "a" (__NR_exit), "D" (code));
}
