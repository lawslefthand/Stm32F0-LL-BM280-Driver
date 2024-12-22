

#ifndef SRC_USART_H_
#define SRC_USART_H_

#define  USART_PIN            (1U<<2)
#define  USART_GPIO_EN        (1U<<17)
#define  USART_EN_CLK         (1U<<17)
#define  USART_GPIO_NAME       GPIOA
#define  USART_EN             (1U<<0)
#define  USART_TE_EN          (1U<<3)
#define  USART_NAME           USART2
#define DESIRED_BAUD_RATE     9600
#define MCU_CLK               8000000
#define  USART_TX_STATUS      (1U<<7)

void usart_init(void);
void usart_gpio_init(void);
int __io_putchar(int ch);
void uart2_write(int ch);
int brr_calc(void);


#endif /* SRC_USART_H_ */
