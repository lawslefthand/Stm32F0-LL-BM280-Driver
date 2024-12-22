#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "stm32f030x8.h"
#include "usart.h"

void usart_init(void) {
	int baud_rate = 69;

	USART_NAME->BRR = baud_rate;

	USART_NAME->CR1 = 0;

	USART_NAME->CR1 = USART_TE_EN;

	USART_NAME->CR1 |= USART_EN;
}

void usart_gpio_init(void) {

	RCC->APB1ENR |= USART_EN_CLK;
	RCC->AHBENR |= USART_GPIO_EN;

	USART_GPIO_NAME->MODER &= ~(1U << 4);
	USART_GPIO_NAME->MODER |= (1U << 5);

	USART_GPIO_NAME->AFR[0] |= (1U << 8);
	USART_GPIO_NAME->AFR[0] &= ~(1U << 9);
	USART_GPIO_NAME->AFR[0] &= ~(1U << 10);
	USART_GPIO_NAME->AFR[0] &= ~(1U << 11);

}

int __io_putchar(int ch) {
	uart2_write(ch);
	return ch;
}

void uart2_write(int ch) {

	while (!(USART2->ISR & USART_TX_STATUS)) {
	}

	USART2->TDR = (ch & 0xFF);
}

int brr_calc(void) {
	int brr_val = ((MCU_CLK + (DESIRED_BAUD_RATE / 2)) / DESIRED_BAUD_RATE);
	return brr_val;
}
