/*
 * uart.h
 *
 *  Created on: 2018. 11. 28.
 *      Author: BYOH
 */
#ifndef UART_H_
#define UART_H_

void Uart0_Init(unsigned int BaudRate);
void Uart0_Tx(char data);
int Uart0_Rx(void);
void Uart0_Irq(void);

void Uart1_Init(void);
void Uart1_Tx(char data);
//int Uart1_Rx(void);
//void Uart1_Irq(void);

void Uart2_Init(unsigned int BaudRate);
void Uart2_Tx(char data);
int Uart2_Rx(void);
void Uart2_Irq(void);

void Uart3_Init(unsigned int BaudRate);
void Uart3_Tx(char data);
int Uart3_Rx(void);
void Uart3_Irq(void);

void Uart4_Init(unsigned int BaudRate);
void Uart4_Tx(char data);
int Uart4_Rx(void);
void Uart4_Irq(void);

void Uart5_Init(unsigned int BaudRate);
void Uart5_Tx(char data);
int Uart5_Rx(void);
void Uart5_Irq(void);

void Uart6_Init(unsigned int BaudRate);
void Uart6_Tx(char data);
int Uart6_Rx(void);
void Uart6_Irq(void);

void Uart7_Init(unsigned int BaudRate);
void Uart7_Tx(char data);
int Uart7_Rx(void);
void Uart7_Irq(void);

void Uart8_Init(unsigned int BaudRate);
void Uart8_Tx(char data);
int Uart8_Rx(void);
void Uart8_Irq(void);


#endif /* UART_H_ */
