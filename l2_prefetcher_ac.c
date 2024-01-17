#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include "memory_1.h"
#include "rte_cycles.h"
#define PAGESIZE 4096
#define CACHE_LINE 64
//int array[256 * 512];

int main(int argc, char *argv[]){
	unsigned int init[3] = {0};
	unsigned int start = 0;
	unsigned int end = 0;
	int evt_stream = atoi(argv[1]);
	int idv_stream = 24;
	char* probe = mmap(NULL, idv_stream * PAGESIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (probe == MAP_FAILED) {
		perror("mmap");
		return -1;
	}
	
	//check_ectlr();	
	//init[0] = 1;
	int offset = 1;
	int step = 5;
	int stride = 5;
	//usleep(1);
	int ret = 0;
	for (int i = 0; i < 1; i++){
		for (int j = 0 ; j < step; j++)
			memory_access_1(probe + j * stride * CACHE_LINE);
	}
	
	asm volatile ("isb");
	for (int i = 0; i < 10000; i++) 
		ret += i;
	//usleep(1);
	//step = 5;
	//stride = 2;
	/*
	for (int j = 0; j < step; j++) {
			memory_access_1(probe + j * stride * CACHE_LINE);
			//Evict memory_access_1 from l1 prefetcher
			memory_access_2(probe + PAGESIZE + j * stride * CACHE_LINE);
			memory_access_3(probe + 2 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_4(probe + 3 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_5(probe + 4 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_6(probe + 5 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_7(probe + 6 * PAGESIZE + j * stride * CACHE_LINE);
		        
			memory_access_8(probe + 7 * PAGESIZE + j * stride * CACHE_LINE);
			
			memory_access_9(probe + 8 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_10(probe + 9 * PAGESIZE + j * stride * CACHE_LINE);		

			memory_access_12(probe + 11 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_13(probe + 12 * PAGESIZE + j * stride * CACHE_LINE);

			memory_access_16(probe + 15 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_17(probe + 16 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_18(probe + 17 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_19(probe + 18 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_20(probe + 19 * PAGESIZE + j * stride * CACHE_LINE);
			memory_access_21(probe + 20 * PAGESIZE + j * stride * CACHE_LINE);

		
	}
	*/	
	step = 5;
	stride = 5;
	memory_access_1(probe + step * stride * CACHE_LINE);
	step = 6;
	char *test_ptr = probe + step * stride * CACHE_LINE;
	char temp = 'x';
	//asm volatile("dsb sy");
	//asm volatile("isb");
	start = rte_rdtsc_precise();
	asm volatile("dsb sy");
	//asm volatile ("isb");
	asm volatile("LDR %0, [%1]\n\t": "=r" (temp): "r" (test_ptr));
	asm volatile ("dsb sy");
	asm volatile ("isb");
	end = rte_rdtsc_precise();


	printf("%d %d\n", evt_stream, end - start);
	
	//printf("Done\n");
	return ret;

}
