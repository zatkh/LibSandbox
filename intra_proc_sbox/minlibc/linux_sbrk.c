#include <sys/syscall.h>
#include <minc.h>

void linux_brk(unsigned long addr)
{
	asm volatile ("syscall" : : "a" (__NR_brk), "D" (addr));
}
