/*
 * uart.c
 *
 *  Created on: 2018. 11. 28.
 *      Author: BYOH
 */
//#include "uart.h"
#include "bits.h"
#include "encoding.h"
#include "print.h"

#define UART_INT_ENABLE


#include "en675.h"
#include "reg.h"

void Uart0_Init(unsigned int BaudRate){UART0_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart0_Tx(char data){while(UART0_TX_FULL);UART0_TX_DAT = data;}
int Uart0_Rx(void){if(UART0_RX_EMPTY) return -1; else return (int)(UART0_RX_DAT & 0xff);}
void Uart0_Irq(void){}

//void Uart1_Init(unsigned int BaudRate){UART1_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
//void Uart1_Tx(char data){while(UART1_TX_FULL);UART1_TX_DAT = data;}
//int Uart1_Rx(void){if(UART1_RX_EMPTY) return -1; else return (int)(UART1_RX_DAT & 0xff);}
//void Uart1_Irq(void){}

void Uart1_Init(){
	volatile unsigned int* ptr = (unsigned int*)0x44a00000;
	*ptr =(unsigned int)0x01a02040;
}

void Uart1_Tx(char data){
	volatile unsigned int* ptr = (unsigned int*)0x44a00010;
	volatile unsigned int* pst = (unsigned int*)0x44a00000;
	while(*pst & 0x20);
	*ptr = (data<<8);
}


void Uart2_Init(unsigned int BaudRate){UART2_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart2_Tx(char data){while(UART2_TX_FULL);UART2_TX_DAT = data;}
int Uart2_Rx(void){if(UART2_RX_EMPTY) return -1; else return (int)(UART2_RX_DAT & 0xff);}
void Uart2_Irq(void){}

void Uart3_Init(unsigned int BaudRate){UART3_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart3_Tx(char data){while(UART3_TX_FULL);UART3_TX_DAT = data;}
int Uart3_Rx(void){if(UART3_RX_EMPTY) return -1; else return (int)(UART3_RX_DAT & 0xff);}
void Uart3_Irq(void){}

void Uart4_Init(unsigned int BaudRate){UART4_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart4_Tx(char data){while(UART4_TX_FULL);UART4_TX_DAT = data;}
int Uart4_Rx(void){if(UART4_RX_EMPTY) return -1; else return (int)(UART4_RX_DAT & 0xff);}
void Uart4_Irq(void){}

void Uart5_Init(unsigned int BaudRate){UART5_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart5_Tx(char data){while(UART5_TX_FULL);UART5_TX_DAT = data;}
int Uart5_Rx(void){if(UART5_RX_EMPTY) return -1; else return (int)(UART5_RX_DAT & 0xff);}
void Uart5_Irq(void){}

void Uart6_Init(unsigned int BaudRate){UART6_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart6_Tx(char data){while(UART6_TX_FULL);UART6_TX_DAT = data;}
int Uart6_Rx(void){if(UART6_RX_EMPTY) return -1; else return (int)(UART6_RX_DAT & 0xff);}
void Uart6_Irq(void){}

void Uart7_Init(unsigned int BaudRate)
{
	SYS_GPIO56_MUX = 3;	//	UART7
	SYS_GPIO57_MUX = 3;	//	UART7
	UART7_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;
}
void Uart7_Tx(char data){while(UART7_TX_FULL);UART7_TX_DAT = data;}
int Uart7_Rx(void){if(UART7_RX_EMPTY) return -1; else return (int)(UART7_RX_DAT & 0xff);}
void Uart7_Irq(void){}

void Uart8_Init(unsigned int BaudRate){UART8_CLK_DIV = (MCK_FREQ/(BaudRate<<4))-1;}
void Uart8_Tx(char data){while(UART8_TX_FULL);UART8_TX_DAT = data;}
int Uart8_Rx(void){if(UART8_RX_EMPTY) return -1; else return (int)(UART8_RX_DAT & 0xff);}
void Uart8_Irq(void){}


#ifdef UART_INT_ENABLE
void Uart1_int_init(void){

  extern char _payload_start, _payload_end;

  volatile unsigned int * pAdr_prio1 = (unsigned int *)0xc000004;
  volatile unsigned int * pAdr_prio2 = (unsigned int *)0xc000008;
  volatile unsigned int * pAdr_mie   = (unsigned int *)0xc002000;
  volatile unsigned int * pAdr_sie   = (unsigned int *)0xc002080;
  volatile unsigned int * pAdr_mthre = (unsigned int *)0xc200000;
  volatile unsigned int * pAdr_sthre = (unsigned int *)0xc201000;
  volatile unsigned int * pAdr_pend  = (unsigned int *)0xc001000;


  *pAdr_prio1 = 1;
  //*pAdr_prio2 = 1;
  *pAdr_mie = 0x2;
  //*pAdr_sie = 0xffffffff;
  *pAdr_mthre = 0x0;
 // *pAdr_sthre = 0x0;

  // Enable External Interrupts
  write_csr(mie, 0x800);

  // Enable Global Interrupts
  unsigned long mstatus = read_csr(mstatus);
  mstatus = INSERT_FIELD(mstatus, MSTATUS_MIE, 1);
  mstatus = INSERT_FIELD(mstatus, MSTATUS_SIE, 1);
  //printm("mstatus = %08lx\n", mstatus);
  write_csr(mstatus, mstatus);

  //printm("plic_m_ie = %08lx\n", *pAdr_mie);
  //printm("plic_s_ie = %08lx\n", *pAdr_sie);
  //printm("plic_prio_sourc1 = %08lx\n", *pAdr_prio1);
  //printm("plic_prio_sourc2 = %08lx\n", *pAdr_prio2);
  //printm("plic m_thre = %08lx\n", *pAdr_mthre);
  //printm("plic s_thre = %08lx\n", *pAdr_sthre);
  //printm("plic pend = %08lx\n", *pAdr_pend);
  unsigned int temp;

}


void IsrUart(void)
{
//	char bBuf;
//
//	while(!Uart1_empty()) {
//		bBuf = Uart1_get();
//
//		if(bBuf == '\r') _printf("\r\n");
//			else {
//			_printf("%c",bBuf);
//		}
//
//
//  }
//  Uart1_clear();
}


void trap_from_machine_mode()
{
	  unsigned long mcause = read_csr(mcause);

	  if ((mcause&0x8000000000000000) != 0x0) {



  volatile unsigned int * pAdr_prio =  (unsigned int *)0xc000004;
  volatile unsigned int * pAdr_mie =   (unsigned int *)0xc002000;
  volatile unsigned int * pAdr_sie =   (unsigned int *)0xc002080;
  volatile unsigned int * pAdr_mthre = (unsigned int *)0xc200000;
  volatile unsigned int * pAdr_sthre = (unsigned int *)0xc201000;
  volatile unsigned int * pAdr_pend =  (unsigned int *)0xc001000;
  volatile unsigned int * pAdr_claim =  (unsigned int *)0xc200004;

  volatile unsigned int source;



 // printm("isr cause = %08lx\n", mcause);
 // printm("isr plic pend = %08lx\n", *pAdr_pend);

  IsrUart();


  source = *pAdr_claim;
//  printm("isr plic claim = %08lx\n", source);
  *pAdr_claim = source;

	  }

}
#endif

