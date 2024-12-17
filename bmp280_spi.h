void bmp_spi_rcc_config() {
	RCC->APB2ENR |= (1 << 12); //spi1 en
	RCC->AHBENR |= (1 << 18); //port b en
	RCC->AHBENR |= (1 << 17); //port a en

}

void bmp_spi_gpio_config() {

	GPIOA->MODER &= ~(1 << 30); //pa 15 alt mode
	GPIOA->MODER |= (1 << 31);

	GPIOB->MODER &= ~(1 << 6); //pb 3 alt mode
	GPIOB->MODER |= (1 << 7);

	GPIOB->MODER &= ~(1 << 8); //pb 4 alt mode
	GPIOB->MODER |= (1 << 9);

	GPIOB->MODER &= ~(1 << 10); //pb 5 alt mode
	GPIOB->MODER |= (1 << 11);

	GPIOB->AFR[0] &= ~(1 << 12);  //pb 3 spi1 sck
	GPIOB->AFR[0] &= ~(1 << 13);
	GPIOB->AFR[0] &= ~(1 << 14);
	GPIOB->AFR[0] &= ~(1 << 15);

	GPIOB->AFR[0] &= ~(1 << 16);  //pb 4 spi1 miso
	GPIOB->AFR[0] &= ~(1 << 17);
	GPIOB->AFR[0] &= ~(1 << 18);
	GPIOB->AFR[0] &= ~(1 << 19);

	GPIOB->AFR[0] &= ~(1 << 20);  //pb 5 spi1 mosi
	GPIOB->AFR[0] &= ~(1 << 21);
	GPIOB->AFR[0] &= ~(1 << 22);
	GPIOB->AFR[0] &= ~(1 << 23);

	GPIOB->AFR[1] &= ~(1 << 28);  //pa 15 spi1 nss
	GPIOB->AFR[1] &= ~(1 << 29);
	GPIOB->AFR[1] &= ~(1 << 30);
	GPIOB->AFR[1] &= ~(1 << 31);

}

void bmp_spi_config() {
	SPI1->CR1 |= (1 << 0) | (1 << 1);   // CPOL=1, CPHA=1

	SPI1->CR1 |= (1 << 2);  // Master Mode

	SPI1->CR1 |= (3 << 3); // BR[2:0] = 011: fPCLK/16, PCLK2 = 80MHz, SPI clk = 5MHz

	SPI1->CR1 |= (1 << 7);  // LSBFIRST = 0, MSB first

	SPI1->CR1 |= (1 << 8) | (1 << 9); // SSM=1, SSi=1 -> Software Slave Management

	SPI1->CR1 &= ~(1 << 10);  // RXONLY = 0, full-duplex

	SPI1->CR1 &= ~(1 << 11);  // DFF=0, 8 bit data

	SPI1->CR2 = 0;
}

