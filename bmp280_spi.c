#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "stm32f030x8.h"

void delay_1s_spi() {
	for (uint32_t i = 0; i < 80000; i++) {
		__asm__("nop");
	}
}

void bmp_spi_rcc_config() {
	RCC->APB2ENR |= (1 << 12); //spi1 en
	RCC->AHBENR |= (1 << 17); //port a en

}

void nss_pu() {

	GPIOA->MODER |= (1 << 8); //pa 4 normal mode
	GPIOA->MODER &= ~(1 << 9);

	GPIOA->BSRR |= (1 << 4);  //bit high

	GPIOA->MODER &= ~(1 << 8); //pa 4 alt mode
	GPIOA->MODER |= (1 << 9);

	GPIOA->AFR[0] &= ~(1 << 16);  //pa 4 spi1 nss
	GPIOA->AFR[0] &= ~(1 << 17);
	GPIOA->AFR[0] &= ~(1 << 18);
	GPIOA->AFR[0] &= ~(1 << 19);

}

void bmp_spi_gpio_config() {

	GPIOA->MODER &= ~(1 << 14); //pa 7 alt mode
	GPIOA->MODER |= (1 << 15);

	GPIOA->MODER &= ~(1 << 12); //pb 6 alt mode
	GPIOA->MODER |= (1 << 13);

	GPIOA->MODER &= ~(1 << 8); //pa 4 alt mode
	GPIOA->MODER |= (1 << 9);

	GPIOA->MODER &= ~(1 << 10); //pa 5 alt mode
	GPIOA->MODER |= (1 << 11);

	GPIOB->AFR[0] &= ~(1 << 24);  //pa 6 spi1 miso
	GPIOB->AFR[0] &= ~(1 << 25);
	GPIOB->AFR[0] &= ~(1 << 26);
	GPIOB->AFR[0] &= ~(1 << 27);

	GPIOA->AFR[0] &= ~(1 << 16);  //pa 4 spi1 nss
	GPIOA->AFR[0] &= ~(1 << 17);
	GPIOA->AFR[0] &= ~(1 << 18);
	GPIOA->AFR[0] &= ~(1 << 19);

	GPIOA->AFR[0] &= ~(1 << 20);  //pa 5 spi1 sck
	GPIOA->AFR[0] &= ~(1 << 21);
	GPIOA->AFR[0] &= ~(1 << 22);
	GPIOA->AFR[0] &= ~(1 << 23);

	GPIOB->AFR[0] &= ~(1 << 28);  //pa 7 spi1 mosi
	GPIOB->AFR[0] &= ~(1 << 29);
	GPIOB->AFR[0] &= ~(1 << 30);
	GPIOB->AFR[0] &= ~(1 << 31);

}

void bmp_spi_config() {
	SPI1->CR1 &= ~(1 << 0);  // CPOL=0, CPHA=0
	SPI1->CR1 &= ~(1 << 1);   // CPOL=0, CPHA=0

	SPI1->CR1 |= (1 << 2);  // Master Mode

	SPI1->CR1 |= (3 << 3); // BR[2:0] = 011: fPCLK/16, PCLK2 = 80MHz, SPI clk = 5MHz

	SPI1->CR1 &= ~(1 << 7);  // LSBFIRST = 0, MSB first

	SPI1->CR1 |= (1 << 13);   //crc en

	SPI1->CR1 &= ~(1 << 8); // SSM=0, SSi=0-> Hardware Slave Management
	SPI1->CR1 &= ~(1 << 9); // SSM=0, SSi=0 -> Hardware Slave Management

	SPI1->CR1 &= ~(1 << 10);  // RXONLY = 0, full-duplex

	SPI1->CR1 &= ~(1 << 11);  // DFF=0, 8 bit data

	SPI1->CR1 |= (1 << 3); //Lowest clk
	SPI1->CR1 |= (1 << 4);
	SPI1->CR1 |= (1 << 5);

	SPI1->CR2 &= ~(1 << 4); //Motorola mode

	SPI1->CR2 |= (1 << 2); // NSS Enabled

	SPI1->CR2 &= ~(1 << 3);

	SPI1->CR2 |= (1 << 12);

	SPI1->CR1 |= SPI_CR1_SPE;  //Periph enable

}

/*
 uint8_t bmp_spi_write(uint8_t tx_addr) {
 uint8_t rx_data = 0;

 /////////////////////////// Transmit Register Address ///////////////////////////
 while (!(SPI1->SR & (1 << 1))) {
 // Wait until TXE (Transmit Buffer Empty) is set
 }
 SPI1->DR = reg_addr;  // Send the register address

 while (SPI1->SR & (1 << 7)) {
 // Wait until BSY (Busy) flag is cleared
 }

 // Clear Overrun flag by reading DR and SR
 volatile uint8_t temp = SPI1->DR;
 temp = SPI1->SR;
 } */

uint8_t bmp_spi_read(uint8_t reg_addr) {
	uint8_t rx_data = 0;

	/////////////////////////// Transmit Register Address ///////////////////////////
	while (!(SPI1->SR & (1 << 1))) {
		// Wait until TXE (Transmit Buffer Empty) is set
	}
	SPI1->DR = reg_addr;  // Send the register address

	while (SPI1->SR & (1 << 7)) {
		// Wait until BSY (Busy) flag is cleared
	}

	// Clear Overrun flag by reading DR and SR
	volatile uint8_t temp = SPI1->DR;
	temp = SPI1->SR;

	/////////////////////////// Transmit Dummy Byte ///////////////////////////
	// while (!(SPI1->SR & (1 << 1))) {
	// Wait until TXE is set
	// }
	// SPI1->DR = 0xFF;  // Send one dummy byte

	while (SPI1->SR & (1 << 7)) {
		// Wait until BSY is cleared
	}

	while (!(SPI1->SR & (1 << 0))) {
		// Wait until RXNE (Receive Buffer Not Empty) is set
	}
	rx_data = SPI1->DR;  // Read the received byte

	nss_pu();

	return rx_data;
}

double spi_temperature(int x) {

	unsigned short calib_T1 = 0;
	signed short calib_T2 = 0;
	signed short calib_T3 = 0;
	signed long raw_temperature = 0;
	double var1 = 0;
	double var2 = 0;
	uint32_t t_fine = 0;
	double final_temp = 0;

	//calibT1 lsb r/w
	calib_T1 = bmp_spi_read(0x88);
	//calibT1 msb r/w
	calib_T1 |= (bmp_spi_read(0x89) << 8);

	//printf("calib t1: %hu\n", calib_T1);

	//calibT2 lsb r/w
	calib_T2 = bmp_spi_read(0x8A);
	//calibT2 msb r/w
	calib_T2 |= (bmp_spi_read(0x8B) << 8);

	//printf("calib t2: %hd\n", calib_T2);

	//calibT3 lsb r/w
	calib_T3 = bmp_spi_read(0x8C);
	//calibT3 msb r/w
	calib_T3 |= (bmp_spi_read(0x8D) << 8);

	//printf("calib t3: %hd\n", calib_T3);

	//	delay_1s_spi();
	raw_temperature = bmp_spi_read(0xFA) << 12;   // msb  << 12;
	//	delay_1s_spi();
	raw_temperature |= bmp_spi_read(0xFB) << 4;   // lsb
	//	delay_1s_spi();
	raw_temperature |= bmp_spi_read(0xFC) >> 4;   // xlsb (upper 4 bits only)

	// printf("raw temp: %ld\n", raw_temperature);

	//calc start

	var1 = (((raw_temperature / 16384.0) - (calib_T1 / 1024.0)) * calib_T2);
	var2 = (((raw_temperature / 131072.0) - (calib_T1 / 8192.0))
			* ((raw_temperature / 131072.0) - (calib_T1 / 8192.0)) * calib_T3);
	t_fine = var1 + var2;
	final_temp = t_fine / 5120.0;

//printf("final temp: %f\n", final_temp);

	if (x == 1) {
		return t_fine;
	} else if (x == 0) {
		return final_temp;
	} else {
		return 0;
	}
}

double spi_pressure() {

	double var1 = 0;
	double var2 = 0;
	unsigned short dig_P1 = 0;
	short dig_P2 = 0;
	short dig_P3 = 0;
	short dig_P4 = 0;
	short dig_P5 = 0;
	short dig_P6 = 0;
	short dig_P7 = 0;
	short dig_P8 = 0;
	short dig_P9 = 0;
	uint32_t t_fine = 0;
	signed long raw_pressure = 0;
	double p = 0;

//   temp = temperature(0);
	t_fine = spi_temperature(1);

	//	dig_P1 lsb r/w
	dig_P1 = bmp_spi_read(0x8E);
	//dig_p1 msb r/w
	dig_P1 |= (bmp_spi_read(0x8F) << 8);

	//dig_P2 lsb r/w
	dig_P2 = bmp_spi_read(0x90);
	//dig_P2 msb r/w
	dig_P2 |= (bmp_spi_read(0x91) << 8);

	// dig_P3 (0x92 / 0x93)
	dig_P3 = bmp_spi_read(0x92);
	dig_P3 |= (bmp_spi_read(0x93) << 8);

	// dig_P4 (0x94 / 0x95)
	dig_P4 = bmp_spi_read(0x94);
	dig_P4 |= (bmp_spi_read(0x95) << 8);

	// dig_P5 (0x96 / 0x97)
	dig_P5 = bmp_spi_read(0x96);
	dig_P5 |= (bmp_spi_read(0x97) << 8);

	// dig_P6 (0x98 / 0x99)
	dig_P6 = bmp_spi_read(0x98);
	dig_P6 |= (bmp_spi_read(0x99) << 8);

	// dig_P7 (0x9A / 0x9B)
	dig_P7 = bmp_spi_read(0x9A);
	dig_P7 |= (bmp_spi_read(0x9B) << 8);

	// dig_P8 (0x9C / 0x9D)
	dig_P8 = bmp_spi_read(0x9C);
	dig_P8 |= (bmp_spi_read(0x9D) << 8);

	// dig_P9 (0x9E / 0x9F)
	dig_P9 = bmp_spi_read(0x9E);
	dig_P9 |= (bmp_spi_read(0x9F) << 8);

	raw_pressure = bmp_spi_read(0xF7) << 12;   // msb << 12;
	raw_pressure |= bmp_spi_read(0xF8) << 4;   // lsb
	raw_pressure |= bmp_spi_read(0xF9) >> 4;   // xlsb

	var1 = ((double) t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double) dig_P6) / 32768.0;
	var2 = var2 * var1 * ((double) dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double) dig_P4) * 65536.0);
	var1 = (((double) dig_P3) * var1 * var1 / 524288.0
			+ ((double) dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * ((double) dig_P1);
	p = 1048576.0 - (double) raw_pressure;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = ((double) dig_P9) * p * p / 2147483648.0;
	var2 = p * ((double) dig_P8) / 32768.0;
	p = p + (var1 + var2 + ((double) dig_P7)) / 16.0;

	printf("final pressure : %f Pa\n", p);

	return p;
}
