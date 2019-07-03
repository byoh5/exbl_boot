
#include "uart.h"
#include "print.h"
#include "boot.h"
#include "ddr.h"
#include "encoding.h"
#include <stdint.h>
#include <string.h>
#include "reg.h"

#define SIZE_OF_DATA 1024*16
int g_test_data = 0;

char g_key=0x0;


#define SLEEP_CNT 100000

#define BASE_ADDR 0x80003000


void sleep_(int cnt)
{

	for(int i=0;i<cnt;i++){
		asm volatile("nop" : :);
	}

}

//#define SFLS_BASE 0xc0000000
//#define SFLS_SIZE 16*1024*1024
#define BOOT_ADDRESS 0
void main_(void)
{
  printf("exception\n");
  while(1);
}

void call(unsigned long addr)
{
  	asm volatile("jalr\t\t%0" : : "r" (addr));
  	asm volatile("nop" : :);
}

void main_0(void)
{



	SYS_REG0 = 0;
    _init_data_section();
     _init_bss_section();
	 Uart7_Init(115200);
	 printf("This is CPU 0\n");





 DdrInit(2);

 int id = read_csr(mhartid);
 _printf("This is CPU : %d\n",id); // ADD some ...
 int targetArea = id + 1;
 unsigned int *pSfls = (unsigned int*)0xc0010000;//(unsigned int*)SFLS_BASE;
 tCodeMemInfo *pCodeMemInfo;
 const char *cpu_str[] = {"CPU0", "CPU1"};
 // Find its FMA
// 	for(int i=0; i<targetArea; i++) pSfls += (*pSfls>>2);

 printf("CPU ID(%d), Binary(0x%X)\r\n", id, pSfls);
 // Get code memory information
 pCodeMemInfo = (tCodeMemInfo *)pSfls;

 unsigned int fma_base = (unsigned int) BOOT_ADDRESS;

 //PRINT_CODE_MEM_INFO(cpu_str[id], fma_base);

	// Code and data copy
	for(int i=CODE_SECTION_IDX(RESET); i<=CODE_SECTION_IDX(DATA); i++)
	{

		unsigned int vma_s = pCodeMemInfo->section[i].s;
		unsigned int vma_e = pCodeMemInfo->section[i].e;
		unsigned int lma_s = pCodeMemInfo->section[VMA_TO_LMA(i)].s;
		unsigned int len = vma_e - vma_s;

		if((lma_s>=SFLS_BASE || lma_s <SFLS_BASE+SFLS_SIZE) &&					// a section in flash
			(vma_s <SFLS_BASE || vma_s>=SFLS_BASE+SFLS_SIZE) &&					// its VMA is not in flash
			len>0)
		{
			//_printf("0x%08X <= 0x%08X (size:%d)\r\n", vma_s, (fma_base+lma_s), len);
			memcpy((void *)(intptr_t)vma_s, (void *)(intptr_t)(fma_base+lma_s),len);			// Flash to SRAM/DDR by DMA

		}
	}
	SYS_REG0 |= 0x1;
	call(0x80000100);

}

void main_1(void)
{
	 sleep_(SLEEP_CNT);
	Uart7_Init(115200);
	 int hartid = read_csr(mhartid);
//	  _printf("This is CPU : %d\n",hartid);
	 while(!(SYS_REG0 & 0x01));
	 sleep_(SLEEP_CNT);
	 SYS_REG0 |= 0x2;
	 call(0x80000100);
}

void main_2(void)
{
	 sleep_(SLEEP_CNT);
	Uart7_Init(115200);
	 int hartid = read_csr(mhartid);
//	  _printf("This is CPU : %d\n",hartid);
	 while(!(SYS_REG0 & 0x01));
	 sleep_(SLEEP_CNT);
	 SYS_REG0 |= 0x4;
	 call(0x80000100);
}

void main_3(void)
{
	 sleep_(SLEEP_CNT);
	Uart7_Init(115200);
	 int hartid = read_csr(mhartid);
//	  _printf("This is CPU : %d\n",hartid);
	 while(!(SYS_REG0 & 0x01));
	 sleep_(SLEEP_CNT);
	 SYS_REG0 |= 0x8;
	 call(0x80000100);
}


