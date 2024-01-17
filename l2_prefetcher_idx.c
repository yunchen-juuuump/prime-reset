#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include "memory_1.h"
#include "rte_cycles.h"

#define __USE_GNU
#include <ucontext.h>

#define PAGESIZE 4096
#define CACHE_LINE 64
int array[256 * 512];

/*
void memory_access_1(char *ptr) {
	unsigned long val64;
	asm volatile("LDR %0, [%1]\n\t": "=r" (val64): "r" (ptr));
}

void memory_access_2(char *ptr) {
	unsigned long val64;
	asm volatile("LDR %0, [%1]\n\t": "=r" (val64): "r" (ptr));
}
*/
/*
void segfault_sigaction(int signal, siginfo_t *si, void *arg)
{
	    printf("Caught segfault at address %p\n", si->si_addr);
	    
	    //return;
	    //exit(0);
}

void sighandler(int signo, siginfo_t *si, ucontext_t* context)
{
	  printf("Handler executed for signal %d\n", signo);
	   //context->uc_mcontext.gregs[REG_RAX] = &n;
}
*/
int main(int argc, char *argv[]){
	unsigned int init[3] = {0};
	unsigned int start = 0;
	unsigned int end = 0;
	/*
	struct sigaction sa;
	
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_sigaction;
	sa.sa_flags   = SA_SIGINFO;
	*/
	//init[256 * PAGESIZE] = 100;
	signal(SIGSEGV, SIG_IGN);
	//sigaction(SIGSEGV, &sa, NULL);
	
	int idv_stream;
	idv_stream = 2;

	//signal(SIGSEGV, sighandler);
	char* probe = mmap(NULL, idv_stream * PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_LOCKED | MAP_ANONYMOUS, -1, 0);	
	
	//init[256 * PAGESIZE] = 100;
	int offset = 10;
	int step = 4;
	int stride = 5;
	 
	//probe[256 * PAGESIZE] = 'x';	
	//int ret = raise(SIGSEGV);
	
	/*
	for (int i = 0; i < 100000;i++) {
		asm volatile("nop");
		asm volatile("isb");
	}
	*/
	for (int i = 0; i < offset; i+=1) {
		for (int j = 0; j < step; j++) {
			memory_access_0(probe + j * stride * CACHE_LINE);	
		}
	}	
	step = 5;
	memory_access_0(probe + 4096 + step * stride  * CACHE_LINE);

	//step = 5;
	//memory_access_0(probe + step * stride  * CACHE_LINE);
	step = 6;
	char *test_ptr = probe + 4096 + step * stride * CACHE_LINE;
	char temp = 'x';
	//enable_cycle_counter_el0();
	start = rte_rdtsc_precise();
	//asm volatile ("dsb sy");
	asm volatile ("isb");
	asm volatile("LDR %0, [%1]\n\t": "=r" (temp): "r" (test_ptr));
	asm volatile ("dsb sy");
	asm volatile ("isb");
	end = rte_rdtsc_precise();

	//asm volatile("mrs %0, PMCCNTR_EL0" : "=r" (end));
	//foo(); //This is my function 
	//readticks(end, 1);

	//end[0] = end[0] - start[0] - overhead;
	printf("Cycles: %d\n", end - start);
	
	//printf("finish\n");
	return 0;

}
